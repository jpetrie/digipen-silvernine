#!perl
# Perl Script for generating new Packet files
# Uses a set of template files & a regular expression
# to find and replace the Packet name
# Author:	plaukait

#USE (Windows w/ActivePerl): [script name] [arguments]
#USE (UNIX w/chmod for executable): [script name] [arguments]

@PackTemplates = qw / CPacket_ CPacket_ CPacketFactory_ CPacketFactory_  /;
@Extensions = qw/ .cpp .h .cpp .h /;
$Name = $ARGV[0];

print "Generating Packet files with Name = $Name";

for($i = 0; $i < 4; $i++)
{
	open OUT, ">$PackTemplates[$i]$Name$Extensions[$i]"
		or die "Could not open $PackTemplates[$i]$Name$Extensions[$i]";
	open TEMPLATE, "<templates_mkPacket\\$PackTemplates[$i]TEMPLATE$Extensions[$i]"
		or die "Could not open templates_mkPacket\\$PackTemplates[$i]TEMPLATE$Extensions[$i]";
	
	foreach (<TEMPLATE>)
	{
		s/TEMPLATE/$Name/g;
		print OUT "$_";
	}
	
	close(OUT);
	close(TEMPLATE);
}
