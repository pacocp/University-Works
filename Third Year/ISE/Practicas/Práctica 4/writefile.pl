#!/usr/bin/perl


use strict;
use warnings;

my $filename = shift @ARGV;

open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
my $i = 0;
for my $i (0..1000000) {
      print $fh $i;
  }

close $fh;
