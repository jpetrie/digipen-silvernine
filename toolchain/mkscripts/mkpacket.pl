#!perl
# Perl Script for generating new Packet files
# Uses a set of template files & a regular expression
# to find and replace the Packet name
# Author:	plaukait

#USE [script name] [Packet Name] [Packet Four Code]

@PackTemplates = qw / CPacket_ CPacket_ CPacketFactory_ CPacketFactory_  /;
@Extensions = qw/ .cpp .h .cpp .h /;
$Name = $ARGV[0];
$Fourcode = $ARGV[1];

$F0 = substr($Fourcode, 0, 1);
$F1 = substr($Fourcode, 1, 1);
$F2 = substr($Fourcode, 2, 1);
$F3 = substr($Fourcode, 3, 1);

print "\nGenerating Packet files with the name $Name\n";

for($i = 0; $i < 4; $i++)
{
	open OUT, ">output_mkpacket\\$PackTemplates[$i]$Name$Extensions[$i]"
		or die "Could not open output_mkpacket\\$PackTemplates[$i]$Name$Extensions[$i]";
		
	open TEMPLATE, "<templates_mkPacket\\$PackTemplates[$i]TEMPLATE$Extensions[$i]"
		or die "Could not open templates_mkPacket\\$PackTemplates[$i]TEMPLATE$Extensions[$i]";
	
	print "Creating $PackTemplates[$i]$Name$Extensions[$i]...\n";
	
	foreach (<TEMPLATE>)
	{
		# Replace each instance of TEMPLATE with the name provided
		s/TEMPLATE/$Name/g;
		
		# Insert the fourcode 
		s/PACKET_CONSTANT_ID_HERE/'$F0', '$F1', '$F2', '$F3'/g;
		
		print OUT "$_";
	}
	
	close(OUT);
	close(TEMPLATE);
}

print "Packet Generation is complete!\n";