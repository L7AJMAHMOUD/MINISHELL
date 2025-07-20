#!/bin/bash

# Script de tests agressifs pour l'expansion du minishell
# Usage: ./test_minishell.sh [path_to_minishell]

MINISHELL=${1:-"./minishell"}
TOTAL_TESTS=0
FAILED_TESTS=0
PASSED_TESTS=0

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Variables d'environnement pour les tests
export TEST_VAR="hello_world"
export EMPTY_VAR=""
export SPECIAL_CHARS="test\$with\$dollars"
export MULTILINE_VAR=$'line1\nline2\nline3'

print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}  TESTS AGRESSIFS MINISHELL EXPANSION${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo ""
}

print_test() {
    local test_name="$1"
    local input="$2"
    echo -e "${YELLOW}Test: $test_name${NC}"
    echo -e "Input: ${BLUE}'$input'${NC}"
}

run_test() {
    local test_name="$1"
    local input="$2"
    local expected="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    print_test "$test_name" "$input"
    
    # Obtenir le résultat attendu de bash
    if [ -z "$expected" ]; then
        expected=$(bash -c "echo $input" 2>/dev/null || echo "ERROR")
    fi
    
    # Obtenir le résultat du minishell
    actual=$(echo "$input" | timeout 5s "$MINISHELL" 2>/dev/null | head -1)
    exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}✗ TIMEOUT${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    elif [ "$actual" = "$expected" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo -e "  Expected: ${GREEN}'$expected'${NC}"
        echo -e "  Got:      ${RED}'$actual'${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# Tests de base
test_basic_expansion() {
    echo -e "${BLUE}=== TESTS DE BASE ===${NC}"
    
    run_test "Variable simple" 'echo $USER'
    run_test "Variable avec accolades" 'echo ${USER}'
    run_test "Variable inexistante" 'echo $NONEXISTENT'
    run_test "Variable vide" 'echo $EMPTY_VAR'
    run_test "PWD expansion" 'echo $PWD'
}

# Tests avec quotes
test_quote_expansion() {
    echo -e "${BLUE}=== TESTS AVEC QUOTES ===${NC}"
    
    run_test "Double quotes simples" '"$USER"'
    run_test "Single quotes (pas d'expansion)" "'$USER'"
    run_test "Mélange quotes" '"hello"$USER"world"'
    run_test "Quotes imbriquées" '"'"'"$USER"'"'"'
    run_test "Double quotes avec espaces" '"hello $USER world"'
}

# Tests agressifs avec quotes multiples
test_aggressive_quotes() {
    echo -e "${BLUE}=== TESTS AGRESSIFS QUOTES ===${NC}"
    
    run_test "Quotes multiples simples" "\"'''''''''''''''''''''''''''''''''\"$PWD\"'''''''''''''''''''''''''''''''''"
    run_test "Alternance quotes" "'\"'\"'\"'\"'$USER'\"'\"'\"'\"'"
    run_test "Quotes avec variables multiples" '"$USER$PWD$HOME"'
    run_test "Quotes avec dollars échappés" '"hello\$world$USER"'
    run_test "Empty quotes avec vars" '""$USER""'
}

# Tests avec variables spéciales
test_special_variables() {
    echo -e "${BLUE}=== VARIABLES SPECIALES ===${NC}"
    
    run_test "Exit status" 'echo $?'
    run_test "Process ID" 'echo $$'
    run_test "Variables avec chiffres" 'echo $1 $2 $3'
    run_test "Variable underscore" 'echo $_'
}

# Tests edge cases
test_edge_cases() {
    echo -e "${BLUE}=== EDGE CASES ===${NC}"
    
    run_test "Dollar seul" 'echo $'
    run_test "Dollars multiples" 'echo $$$'
    run_test "Variable avec caractères spéciaux" 'echo $USER@host'
    run_test "Variable incomplete" 'echo ${USER'
    run_test "Accolades vides" 'echo ${}'
    run_test "Dollar échappé" 'echo \$USER'
    run_test "Backslash avant variable" 'echo \\$USER'
}

# Tests de performance/stress
test_stress() {
    echo -e "${BLUE}=== TESTS DE STRESS ===${NC}"
    
    # Longue chaîne avec beaucoup de variables
    long_vars=""
    for i in {1..50}; do
        long_vars="${long_vars}\$USER"
    done
    run_test "50 variables consécutives" "echo $long_vars"
    
    # Quotes très longues
    long_quotes="'"
    for i in {1..100}; do
        long_quotes="${long_quotes}'"
    done
    long_quotes="${long_quotes}\$PWD"
    for i in {1..100}; do
        long_quotes="${long_quotes}'"
    done
    run_test "200 single quotes" "echo $long_quotes"
    
    # Variables imbriquées complexes
    run_test "Variables imbriquées" 'echo ${USER}${PWD}${HOME}${USER}'
}

# Tests avec caractères spéciaux
test_special_chars() {
    echo -e "${BLUE}=== CARACTERES SPECIAUX ===${NC}"
    
    run_test "Espaces dans expansion" 'echo "$USER world"'
    run_test "Tabs et newlines" $'echo "$USER\t$PWD\n"'
    run_test "Caractères unicode" 'echo "éàù$USER"'
    run_test "Pipe et redirection" 'echo $USER | cat'
    run_test "Ampersand" 'echo $USER & wait'
}

# Tests d'erreurs
test_error_cases() {
    echo -e "${BLUE}=== TESTS D'ERREURS ===${NC}"
    
    run_test "Quote non fermée" "echo \"hello world"
    run_test "Accolade non fermée" "echo \${USER"
    run_test "Caractère null" $'echo $USER\0test'
    run_test "Très long nom de variable" "echo \$$(printf 'A%.0s' {1..1000})"
}

# Tests de compatibilité bash
test_bash_compatibility() {
    echo -e "${BLUE}=== COMPATIBILITE BASH ===${NC}"
    
    run_test "Expansion avec arithmétique" 'echo $((1+1))'
    run_test "Substitution de commande" 'echo $(echo hello)'
    run_test "Expansion de paramètres" 'echo ${USER:-default}'
    run_test "Pattern matching" 'echo ${USER%/*}'
}

print_summary() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}           RESULTATS FINAUX${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo -e "Total tests:  $TOTAL_TESTS"
    echo -e "${GREEN}Réussis:      $PASSED_TESTS${NC}"
    echo -e "${RED}Échoués:      $FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}🎉 TOUS LES TESTS SONT PASSÉS ! 🎉${NC}"
        exit 0
    else
        echo -e "${RED}❌ $FAILED_TESTS tests ont échoué${NC}"
        exit 1
    fi
}

# Vérifier que le minishell existe
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Erreur: Minishell '$MINISHELL' introuvable${NC}"
    echo "Usage: $0 [path_to_minishell]"
    exit 1
fi

# Exécuter tous les tests
print_header

test_basic_expansion
test_quote_expansion
test_aggressive_quotes
test_special_variables
test_edge_cases
test_stress
test_special_chars
test_error_cases
test_bash_compatibility

print_summary