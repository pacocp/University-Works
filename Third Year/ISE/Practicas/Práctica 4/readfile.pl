#!/usr/bin/perl


use strict;
use warnings;

my $filename = shift @ARGV;

open(my $fh, '<:encoding(UTF-8)', $filename)
  or die "Could not open file '$filename' $!";

  while (my $row = <$fh>) {
    chomp $row;
    my $fila =  "$row\n";
  }
