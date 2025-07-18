#!/bin/bash

# Script de test complet pour Minishell
# Usage: ./test_minishell.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Testing Minishell for Segfaults and Errors ===${NC}"

# Vérifier si minishell existe
if [ ! -f "./minishell" ]; then
    echo -e "${RED}❌ minishell not found. Compile first with: make${NC}"
    exit 1
fi

# Compteurs
total_tests=0
segfaults=0
timeouts=0
errors=0
success=0

# Fonction pour tester une commande
test_command() {
    local cmd="$1"
    local expected_behavior="$2"
    
    echo -e "${YELLOW}Testing: ${cmd}${NC}"
    total_tests=$((total_tests + 1))
    
    # Exécuter la commande avec timeout
    echo "$cmd" | timeout 5 ./minishell 2>/dev/null
    exit_code=$?
    
    case $exit_code in
        0)
            echo -e "${GREEN}✅ OK${NC}"
            success=$((success + 1))
            ;;
        139)
            echo -e "${RED}💥 SEGFAULT detected!${NC}"
            segfaults=$((segfaults + 1))
            ;;
        124)
            echo -e "${YELLOW}⏰ TIMEOUT (>5s)${NC}"
            timeouts=$((timeouts + 1))
            ;;
        127)
            echo -e "${YELLOW}⚠️  Exit code 127 (command not found or shell exit issue)${NC}"
            errors=$((errors + 1))
            ;;
        *)
            echo -e "${YELLOW}⚠️  Exit code: $exit_code${NC}"
            errors=$((errors + 1))
            ;;
    esac
    
    if [ -n "$expected_behavior" ]; then
        echo -e "${BLUE}   Expected: $expected_behavior${NC}"
    fi
    
    echo "---"
}

# Fonction pour tester une commande avec gestion d'erreur spécifique
test_command_with_error_handling() {
    local cmd="$1"
    local expected_behavior="$2"
    local should_fail="$3"
    
    echo -e "${YELLOW}Testing: ${cmd}${NC}"
    total_tests=$((total_tests + 1))
    
    # Créer un fichier temporaire pour capturer la sortie
    local temp_output=$(mktemp)
    
    # Exécuter la commande avec timeout et capturer la sortie
    echo "$cmd" | timeout 10 ./minishell > "$temp_output" 2>&1
    exit_code=$?
    
    # Afficher la sortie si elle existe
    if [ -s "$temp_output" ]; then
        echo -e "${BLUE}Output: $(cat "$temp_output")${NC}"
    fi
    
    case $exit_code in
        0)
            if [ "$should_fail" = "true" ]; then
                echo -e "${YELLOW}⚠️  Expected failure but got success${NC}"
                errors=$((errors + 1))
            else
                echo -e "${GREEN}✅ OK${NC}"
                success=$((success + 1))
            fi
            ;;
        139)
            echo -e "${RED}💥 SEGFAULT detected!${NC}"
            segfaults=$((segfaults + 1))
            ;;
        124)
            echo -e "${YELLOW}⏰ TIMEOUT (>10s)${NC}"
            timeouts=$((timeouts + 1))
            ;;
        127)
            echo -e "${YELLOW}⚠️  Exit code 127 (command not found or shell exit issue)${NC}"
            errors=$((errors + 1))
            ;;
        *)
            echo -e "${YELLOW}⚠️  Exit code: $exit_code${NC}"
            errors=$((errors + 1))
            ;;
    esac
    
    if [ -n "$expected_behavior" ]; then
        echo -e "${BLUE}   Expected: $expected_behavior${NC}"
    fi
    
    rm -f "$temp_output"
    echo "---"
}

echo -e "${BLUE}=== 1. Tests basiques ===${NC}"
test_command 'echo "hello world"' "Affichage simple"
test_command 'echo hello' "Echo sans quotes"
test_command 'pwd' "Affichage du répertoire courant"
test_command '/bin/echo test' "Commande avec chemin absolu"

echo -e "${BLUE}=== 2. Tests des variables d'environnement ===${NC}"
test_command 'echo $HOME' "Affichage de HOME"
test_command 'echo $USER' "Affichage de USER"
test_command 'echo $PATH' "Affichage de PATH"
test_command 'echo $?' "Code de retour précédent"
test_command 'echo $NONEXISTENT' "Variable inexistante (doit être vide)"
test_command 'echo $' "Dollar seul"
test_command 'echo $$' "PID du shell"

echo -e "${BLUE}=== 3. Tests des quotes ===${NC}"
test_command 'echo "hello world"' "Double quotes"
test_command "echo 'hello world'" "Single quotes"
test_command 'echo "hello $USER"' "Expansion dans double quotes"
test_command "echo 'hello \$USER'" "Pas d'expansion dans single quotes"
test_command_with_error_handling 'echo """' "Triple double quotes" "true"
test_command_with_error_handling "echo '''" "Triple single quotes" "true"
test_command_with_error_handling 'echo "hello' "Quote non fermée" "true"
test_command_with_error_handling "echo 'hello" "Quote mixte non fermée" "true"
test_command 'echo "hello'"'"'world"' "Quotes imbriquées"

echo -e "${BLUE}=== 4. Tests d'expansion problématiques ===${NC}"
test_command 'echo $$$' "Triple dollar"
test_command 'echo $1$2$3' "Variables positionnelles"
test_command 'echo ${HOME}' "Expansion avec accolades (si supportée)"
test_command 'echo $HOME$USER' "Concaténation de variables"
test_command 'echo "$HOME/$USER"' "Variables dans quotes"
test_command 'echo $0' "Nom du shell"

echo -e "${BLUE}=== 5. Tests de pipes ===${NC}"
test_command 'echo hello | cat' "Pipe simple"
test_command 'echo hello | cat | cat' "Pipe double"
test_command 'ls | grep minishell' "Pipe avec grep"
test_command_with_error_handling 'echo hello |' "Pipe incomplete" "true"
test_command_with_error_handling '| echo hello' "Pipe au début" "true"
test_command_with_error_handling 'echo hello | | cat' "Double pipe" "true"

echo -e "${BLUE}=== 6. Tests de redirections ===${NC}"
test_command 'echo hello > /tmp/test_file' "Redirection sortie"
test_command 'cat < /tmp/test_file' "Redirection entrée"
test_command 'echo world >> /tmp/test_file' "Redirection append"
test_command 'cat /tmp/test_file' "Lecture du fichier créé"
test_command 'echo hello > /tmp/test1 > /tmp/test2' "Double redirection"
test_command_with_error_handling 'echo hello >' "Redirection incomplete" "true"
test_command_with_error_handling 'echo hello > /root/nopermission' "Redirection vers fichier non accessible" "true"

echo -e "${BLUE}=== 7. Tests de commandes vides et espaces ===${NC}"
test_command '' "Commande vide"
test_command '   ' "Espaces seulement"
test_command 'echo' "Echo sans argument"
test_command '     echo     hello     ' "Espaces multiples"

echo -e "${BLUE}=== 8. Tests de caractères spéciaux ===${NC}"
test_command 'echo "hello; world"' "Point-virgule dans quotes"
test_command 'echo hello; echo world' "Point-virgule (si supporté)"
test_command 'echo "hello && world"' "ET logique dans quotes"
test_command 'echo "hello || world"' "OU logique dans quotes"
test_command 'echo "hello & world"' "Esperluette dans quotes"

echo -e "${BLUE}=== 9. Tests de commandes intégrées ===${NC}"
test_command 'cd /tmp' "Changement de répertoire"
test_command 'pwd' "Vérification du répertoire"
test_command 'cd' "Retour au home"
test_command 'export TEST_VAR=hello' "Export de variable"
test_command 'echo $TEST_VAR' "Utilisation de la variable exportée"
test_command 'unset TEST_VAR' "Suppression de variable"
test_command 'echo $TEST_VAR' "Variable supprimée"
test_command 'env | grep USER' "Affichage des variables d'environnement"

echo -e "${BLUE}=== 10. Tests de stress ===${NC}"
test_command 'echo $HOME$USER$PATH$?$0$$$1$2$3' "Beaucoup de variables"
test_command 'echo "a very long string with $HOME and $USER and quotes and $? and more stuff"' "Chaîne complexe"
test_command 'echo hello | cat | cat | cat | cat | cat' "Pipe très long"

echo -e "${BLUE}=== 11. Tests de cas limites ===${NC}"
test_command 'echo $' "Dollar en fin de ligne"
test_command 'echo $""' "Dollar avec chaîne vide"
test_command 'echo "$"' "Dollar dans quotes"
test_command 'echo \$HOME' "Dollar échappé (si supporté)"
test_command 'echo hello world | cat > /tmp/test_pipe' "Pipe + redirection"

echo -e "${BLUE}=== 12. Tests de gestion des erreurs ===${NC}"
test_command_with_error_handling 'nonexistent_command' "Commande inexistante" "true"
test_command_with_error_handling 'cat /nonexistent/file' "Fichier inexistant" "true"
test_command_with_error_handling 'cd /nonexistent/directory' "Répertoire inexistant" "true"

echo -e "${BLUE}=== 13. Tests de exit ===${NC}"
test_command 'exit 0' "Exit avec code 0"
test_command 'exit 42' "Exit avec code personnalisé"
test_command_with_error_handling 'exit abc' "Exit avec argument non numérique" "true"

# Nettoyage
rm -f /tmp/test_file /tmp/test1 /tmp/test2 /tmp/test_pipe 2>/dev/null

echo -e "${BLUE}=== Résumé des tests ===${NC}"
echo -e "Total tests: $total_tests"
echo -e "${GREEN}✅ Succès: $success${NC}"
echo -e "${RED}💥 Segfaults: $segfaults${NC}"
echo -e "${YELLOW}⏰ Timeouts: $timeouts${NC}"
echo -e "${YELLOW}⚠️  Autres erreurs: $errors${NC}"

if [ $segfaults -gt 0 ]; then
    echo -e "${RED}❌ Des segfaults ont été détectés ! Utilisez GDB pour déboguer :${NC}"
    echo -e "${YELLOW}gdb ./minishell${NC}"
    echo -e "${YELLOW}(gdb) run${NC}"
    echo -e "${YELLOW}# Tapez la commande qui cause le segfault${NC}"
    echo -e "${YELLOW}(gdb) bt${NC}"
    echo -e "${YELLOW}# Pour plus de détails :${NC}"
    echo -e "${YELLOW}(gdb) info registers${NC}"
    echo -e "${YELLOW}(gdb) x/10i \$pc${NC}"
fi

if [ $timeouts -gt 0 ]; then
    echo -e "${YELLOW}⚠️  Des timeouts ont été détectés. Vérifiez les boucles infinies.${NC}"
fi

if [ $errors -gt 0 ]; then
    echo -e "${YELLOW}⚠️  Des erreurs ont été détectées. Points à vérifier :${NC}"
    echo -e "${YELLOW}   - Gestion de la sortie du shell (exit code 127)${NC}"
    echo -e "${YELLOW}   - Parsing des commandes malformées${NC}"
    echo -e "${YELLOW}   - Gestion des erreurs d'exécution${NC}"
fi

if [ $segfaults -eq 0 ] && [ $timeouts -eq 0 ]; then
    echo -e "${GREEN}🎉 Aucun segfault ou timeout détecté !${NC}"
    if [ $errors -eq 0 ]; then
        echo -e "${GREEN}🎉 Tous les tests ont réussi ! Votre minishell semble très stable.${NC}"
    else
        echo -e "${YELLOW}⚠️  Quelques erreurs à corriger mais pas de crashes.${NC}"
    fi
fi

echo -e "${BLUE}=== Conseils de débogage ===${NC}"
echo -e "${YELLOW}1. Pour déboguer les exit codes 127 :${NC}"
echo -e "   - Vérifiez que votre shell retourne 0 après chaque commande réussie"
echo -e "   - Assurez-vous que 'exit' fonctionne correctement"
echo -e "   - Vérifiez la gestion de la boucle principale du shell"

echo -e "${YELLOW}2. Pour améliorer la robustesse :${NC}"
echo -e "   - Ajoutez des vérifications sur les pointeurs NULL"
echo -e "   - Gérez les cas d'erreur de malloc/free"
echo -e "   - Testez avec valgrind : valgrind --leak-check=full ./minishell"

echo -e "${YELLOW}3. Pour tester manuellement :${NC}"
echo -e "   - Lancez ./minishell et testez chaque commande individuellement"
echo -e "   - Utilisez Ctrl+C, Ctrl+D, Ctrl+\\ pour tester la gestion des signaux"
echo -e "   - Testez avec des commandes très longues"