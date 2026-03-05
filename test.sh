#!/bin/bash

# Test script for OcrCaptchaMnn
set -e

echo "========================================"
echo "OCR Captcha Recognition Test"
echo "========================================"

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXECUTABLE="$1"
MODEL_FILE="$2"
TEST_IMAGE="$3"

# Set defaults if not provided
EXECUTABLE="${EXECUTABLE:-build/ocrCaptchaMnn}"
MODEL_FILE="${MODEL_FILE:-ocr.captcha.sim.mnn}"
TEST_IMAGE="${TEST_IMAGE:-captcha.png}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "❌ ERROR: Executable not found: $EXECUTABLE"
    exit 1
fi

# Check if model file exists
if [ ! -f "$MODEL_FILE" ]; then
    echo "❌ ERROR: Model file not found: $MODEL_FILE"
    exit 1
fi

# Check if test image exists
if [ ! -f "$TEST_IMAGE" ]; then
    echo "❌ ERROR: Test image not found: $TEST_IMAGE"
    exit 1
fi

echo ""
echo "Test Configuration:"
echo "  Executable: $EXECUTABLE"
echo "  Model: $MODEL_FILE"
echo "  Test Image: $TEST_IMAGE"
echo ""

# Run test
echo "Running OCR test..."
echo "========================================"

TEST_RESULT=$("$EXECUTABLE" "$MODEL_FILE" "$TEST_IMAGE" 2>&1)
TEST_EXIT_CODE=$?

echo "$TEST_RESULT"
echo "========================================"

# Check result
if [ $TEST_EXIT_CODE -eq 0 ]; then
    echo ""
    echo "✅ Test PASSED"
    
    # Extract recognition result
    RECOGNITION_RESULT=$(echo "$TEST_RESULT" | grep "ocr captcha :" | sed 's/.*ocr captcha : //')
    
    echo ""
    echo "Recognition Results:"
    echo "  Result: $RECOGNITION_RESULT"
    echo ""
    
    exit 0
else
    echo ""
    echo "❌ Test FAILED (Exit code: $TEST_EXIT_CODE)"
    exit 1
fi
