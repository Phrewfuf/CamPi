#!/usr/bin/perl

use strict;
use warnings;
use Time::Piece;

my $listdir_ipad = '/home/phrewfuf/CamPi/piclist_ipad.txt';
my $listdir_cam = '/home/phrewfuf/CamPi/piclist_cam.txt';
my $picdir = '/home/phrewfuf/CamPi';
my $date = Time::Piece->new->strftime('%Y_%m_%d');



print $date;

open(my $piclist, "<",  $listdir) or die "Can't open piclist.txt: $!";

while ($piclist) 
{
}

close($piclist);
exit 0;
