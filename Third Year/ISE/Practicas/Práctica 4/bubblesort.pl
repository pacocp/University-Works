#!/usr/bin/perl

use strict;
use warnings;

my @rand;
my %seen;

my $size=shift @ARGV;

for (1..$size) {
    my $candidate = int rand($size);
    redo if $seen{$candidate}++;
    push @rand, $candidate;
}

for my $i ( 1 .. $#rand ) {
    for my $k ( 0 .. $i - 1 ) {
        @rand[ $k, $k + 1 ] = @rand[ $k + 1, $k ]
            if $rand[$k] > $rand[ $k + 1 ];
    }
}
