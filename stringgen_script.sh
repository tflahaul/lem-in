#!/bin/bash
 touch file; for i in {1..10}; do echo `ruby StringGen.rb` >> file; done;
