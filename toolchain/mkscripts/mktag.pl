
# Arguments:
#  0: tag type string
#  1: tag kind string

  # Setup.
  $code     = @ARGV[0];
  $codename = @ARGV[1];
  $code_a   = substr($code,0,1);
  $code_b   = substr($code,1,1);
  $code_c   = substr($code,2,1);
  $code_d   = substr($code,3,1);
  $code_cap = uc($code);
  
  # Make the tag header file.
  print("Making tag header...\n");
  $filename = "output_mktag/CTag_%%CODE%%.h";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mktag/mktag_classhead_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%CODE%%/$code/g;
      $line =~ s/%%CODECAPPED%%/$code_cap/g;
      $line =~ s/%%CODENAME%%/$codename/g;
      $line =~ s/%%A%%/$code_a/g;
      $line =~ s/%%B%%/$code_b/g;
      $line =~ s/%%C%%/$code_c/g;
      $line =~ s/%%D%%/$code_d/g;
      print(FILEOUT $line);
    }
  }
  
  # Close.
  close(FILEIN);
  close(FILEOUT);
  
  # Make the factory header file.
  print("Making tag factory header...\n");
  $filename = "output_mktag/CTagFactory_%%CODE%%.h";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mktag/mktag_factoryhead_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%CODE%%/$code/g;
      $line =~ s/%%CODECAPPED%%/$code_cap/g;
      $line =~ s/%%CODENAME%%/$codename/g;
      print(FILEOUT $line);
    }
  }

  # Close.
  close(FILEIN);
  close(FILEOUT);
  
  # Make the factory source file.
  print("Making tag factory source...\n");
  $filename = "output_mktag/CTagFactory_%%CODE%%.cpp";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mktag/mktag_factorybody_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%CODE%%/$code/g;
      $line =~ s/%%CODECAPPED%%/$code_cap/g;
      $line =~ s/%%CODENAME%%/$codename/g;
      print(FILEOUT $line);
    }
  }

  # Close.
  close(FILEIN);
  close(FILEOUT);
  
  print("Source code output to output_mktag directory.\n");