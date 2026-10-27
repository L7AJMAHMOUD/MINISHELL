#!/usr/bin/env python3
"""Behavioral regression tests; requires Python 3 and Bash, no pip packages."""
import os
from pathlib import Path
import signal
import pty
import select
import time
import shutil
import subprocess
import sys
import tempfile
import unittest

BINARY = str(Path(sys.argv.pop(1) if len(sys.argv) > 1 else './minishell').resolve())


class ShellTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix='minishell-test-')
        self.addCleanup(self.directory.cleanup)
        self.env = {'PATH': '/usr/bin:/bin', 'HOME': self.directory.name,
                    'PWD': self.directory.name, 'LC_ALL': 'C', 'TERM': 'dumb'}
        for key in ('ASAN_OPTIONS', 'UBSAN_OPTIONS'):
            if key in os.environ:
                self.env[key] = os.environ[key]

    def run_shell(self, script, reference=False):
        command = ['bash', '--noprofile', '--norc'] if reference else [BINARY]
        with subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE, text=True, env=self.env,
                              cwd=self.directory.name, start_new_session=True) as process:
            try:
                out, err = process.communicate(script, timeout=5)
            except subprocess.TimeoutExpired:
                os.killpg(process.pid, signal.SIGKILL)
                process.communicate()
                self.fail(f'Command timed out: {script!r}')
        self.assertNotIn('AddressSanitizer', err)
        self.assertNotIn('LeakSanitizer', err)
        self.assertNotIn('runtime error:', err)
        self.assertNotIn('\x00', err)
        self.assertGreaterEqual(process.returncode, 0, err)
        return out, err, process.returncode

    def clear_files(self):
        for path in Path(self.directory.name).iterdir():
            if path.is_dir() and not path.is_symlink():
                shutil.rmtree(path)
            else:
                path.unlink()

    def compare(self, script):
        self.clear_files()
        expected = self.run_shell(script, reference=True)
        self.clear_files()
        actual = self.run_shell(script)
        self.assertEqual((actual[0], actual[2]), (expected[0], expected[2]),
                         f'{script!r}\nstderr: {actual[1]}')
        self.assertEqual(bool(actual[1]), bool(expected[1]), actual[1])

    def test_commands_and_quotes(self):
        for script in ["", " \t \n", "echo hello world\n", "echo -\n",
                       "echo -n -nn hello\necho world\n", "echo '' \"\" tail\n",
                       "echo 'a b' \"c d\" e'f'g\n", "printf '<%s>\\n' '' hi\n",
                       "echo 'a|b' '<' \"x>y\"\n", "echo last line", "echo a\tb\n", "echo $\n", "echo \"$\"\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_environment(self):
        for script in ["export TEST=hello\necho $TEST\n",
                       "export TEST='hello world'\nprintf '<%s>\\n' \"$TEST\"\n",
                       "export TEST=one\nexport TEST+=two\necho $TEST\n",
                       "export TEST=one\nunset TEST\necho \"$TEST\"\n",
                       "export TEST\nenv | grep '^TEST'\n",
                       "export 1BAD=value\necho $?\nenv | grep '^1BAD'\n",
                       "export TEST=one\nexport TEST\necho $TEST\n",
                       "echo '$HOME'\necho \"$HOME\"\n",
                       "unset DOES_NOT_EXIST\necho $?\n",
                       "export TEST=hello\necho $TEST.txt\n",
                       "export TEST='one two'\nprintf '<%s>\\n' $TEST\n",
                       "$UNSET\n", "echo $UNSET\n", "false\n$UNSET\n",
                       "export TEST='>'\necho $TEST\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_cd(self):
        for script in ["cd\npwd\necho $PWD\n", "cd /\npwd\ncd -\npwd\n",
                       "cd /missing-minishell-directory\necho $?\n",
                       "unset HOME\ncd\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_exit_status(self):
        for script in ["false\n", "false\necho $?\n", "exit\n", "exit 42\n",
                       "exit -1\n", "false\nexit\n", "exit 256\n", "exit +12\n", "exit ''\n",

                       "exit 9223372036854775808\n", "exit -9223372036854775808\n",
                       "missing_minishell_command\n", "/missing/minishell\n", "/tmp\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_cd_excess_arguments(self):
        out, err, status = self.run_shell("cd / /tmp\necho $?\n")
        self.assertEqual((out, status), ("1\n", 0))
        self.assertIn("too many arguments", err)

    def test_exit_errors(self):
        # Explicit policy: invalid numbers terminate; excess arguments do not.
        out, err, status = self.run_shell("exit abc\necho unreachable\n")
        self.assertEqual((out, status), ('', 2))
        self.assertIn('numeric argument required', err)
        out, err, status = self.run_shell("exit 1 2\necho $?\n")
        self.assertEqual((out, status), ('1\n', 0))
        self.assertIn('too many arguments', err)

    def test_pipelines(self):
        for script in ["echo hello | cat\n", "printf 'b\\na\\n' | sort | head -n 1\n",
                       "false | true\n", "true | false\n", "yes | head -n 1\n",
                       "export TEST=value | cat\necho \"$TEST\"\n",
                       "echo hello | cat | wc -c\n", "exit 3 | cat\necho alive\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_redirections(self):
        for script in ["echo first > out\necho second >> out\ncat < out\n",
                       "pwd > out\ncat out\n", "echo hello > 'a b'\ncat 'a b'\n",
                       "> empty\nwc -c < empty\n", "cat < missing_file\necho $?\n",
                       "echo hi > first > second\ncat first second\n",
                       "echo hello | cat > out\ncat out\n",
                       "export FILE='a b'\necho hello > \"$FILE\"\ncat \"$FILE\"\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_heredocs(self):
        for script in ["cat << EOF\nhello\nEOF\n", "cat << EOF\n\nhello\n\nEOF\n",
                       "cat << EOF\n$HOME\nEOF\n", "cat << 'EOF'\n$HOME\nEOF\n",
                       "cat << A << B\none\nA\ntwo\nB\n",
                       "cat << EOF | wc -c\nhello\nEOF\n",
                       "echo file > out\ncat << EOF < out\ndoc\nEOF\n",
                       "cat << EOF\nend without delimiter\n", "cat << EOF\n$\nEOF\n",
                       "cat << A << 'B'\n$HOME\nA\n$HOME\nB\n"]:
            with self.subTest(script=script):
                self.compare(script)

    def test_syntax_errors(self):
        for script in ["| echo bad\n", "echo bad |\n", "echo bad || cat\n",
                       "echo >\n", "echo >>> out\n", "echo 'unclosed\n", "\t| cat\n"]:
            with self.subTest(script=script):
                out, err, code = self.run_shell(script)
                self.assertEqual(code, 2)
                self.assertEqual(out, '')
                self.assertTrue(err)

    def test_repeated_commands(self):
        self.compare(("echo hi | cat\n" * 40) + ("pwd > out\n" * 40) + "cat out\n")

    def test_path_and_permissions(self):
        program = Path(self.directory.name, 'local-command')
        program.write_text('#!/bin/sh\nprintf "local-ok\\n"\n')
        program.chmod(0o755)
        for path in ('', ':', '/missing:', ':/missing'):
            with self.subTest(path=path):
                out, err, status = self.run_shell(f'export PATH={path}\nlocal-command\n')
                self.assertEqual((out, err, status), ('local-ok\n', '', 0))
        program.chmod(0o644)
        out, err, status = self.run_shell('./local-command\n')
        self.assertEqual(status, 126)
        self.assertIn('Permission denied', err)
        out, err, status = self.run_shell('unset PATH\n/missing-command\n')
        self.assertEqual(status, 127)

    def test_empty_environment(self):
        self.env = {key: value for key, value in self.env.items()
                    if key in ('ASAN_OPTIONS', 'UBSAN_OPTIONS')}
        out, err, status = self.run_shell('echo ready\n/usr/bin/true\n')
        self.assertEqual((out, err, status), ('ready\n', '', 0))

    def test_interactive_signals(self):
        pid, terminal = pty.fork()
        if pid == 0:
            os.chdir(self.directory.name)
            os.execve(BINARY, [BINARY], self.env)
        reaped = False

        def read_until(marker):
            output = b''
            deadline = time.monotonic() + 5
            while marker not in output and time.monotonic() < deadline:
                ready, _, _ = select.select([terminal], [], [], 0.1)
                if ready:
                    try:
                        chunk = os.read(terminal, 65536)
                    except OSError:
                        break
                    if not chunk:
                        break
                    output += chunk
            self.assertIn(marker, output, output.decode(errors='replace'))
            self.assertNotIn(b'Sanitizer', output)
            self.assertNotIn(b'runtime error:', output)
            return output

        try:
            read_until(b'minishell$ ')
            os.write(terminal, b'echo interactive\n')
            self.assertIn(b'interactive\r\n', read_until(b'minishell$ '))
            os.write(terminal, b'\x03')
            read_until(b'minishell$ ')
            os.write(terminal, b'echo $?\n')
            self.assertIn(b'130\r\n', read_until(b'minishell$ '))
            for command in (b'sleep 10\n', b'sleep 10 | cat\n', b'cat << EOF\n'):
                os.write(terminal, command)
                if b'<<' in command:
                    read_until(b'> ')
                else:
                    time.sleep(0.15)
                os.write(terminal, b'\x03')
                read_until(b'minishell$ ')
                os.write(terminal, b'echo $?\n')
                self.assertIn(b'130\r\n', read_until(b'minishell$ '))
            os.write(terminal, b'\x04')
            read_until(b'exit')
            deadline = time.monotonic() + 5
            while time.monotonic() < deadline:
                child, status = os.waitpid(pid, os.WNOHANG)
                if child:
                    reaped = True
                    self.assertEqual(os.waitstatus_to_exitcode(status), 0)
                    break
                time.sleep(0.02)
            self.assertTrue(reaped, 'Shell did not exit on Ctrl-D')
        finally:
            if not reaped:
                os.killpg(pid, signal.SIGKILL)
                os.waitpid(pid, 0)
            os.close(terminal)

    def test_cli(self):
        for option, code in [('--help', 0), ('--version', 0), ('--invalid', 2)]:
            with self.subTest(option=option):
                result = subprocess.run([BINARY, option], capture_output=True, timeout=5)
                self.assertEqual(result.returncode, code)


if __name__ == '__main__':
    unittest.main(verbosity=2)
