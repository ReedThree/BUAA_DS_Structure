#!/bin/bash

$1 > $2"_progout"
diff $2"_progout" $3
