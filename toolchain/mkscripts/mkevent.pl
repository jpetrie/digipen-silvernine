
# Arguments:
#  0: event type
#  1: event id code

  # Setup.
  $code     = @ARGV[0];
  $id       = @ARGV[1];
  $code_a   = substr($id,0,1);
  $code_b   = substr($id,1,1);
  $code_c   = substr($id,2,1);
  $code_d   = substr($id,3,1);
  $code_cap = uc($code);
  
  # Make the class header file.
  print("Making event header...\n");
  $filename = "output_mkevent/CEvent_%%CODE%%.h";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mkevent/mkevent_classhead_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%EVENT%%/$code/g;
      $line =~ s/%%EVENTC%%/$code_cap/g;
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
  
  # Make the class source file.
  print("Making event source...\n");
  $filename = "output_mkevent/CEvent_%%CODE%%.cpp";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mkevent/mkevent_classbody_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%EVENT%%/$code/g;
      $line =~ s/%%EVENTC%%/$code_cap/g;
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
  print("Making factory header...\n");
  $filename = "output_mkevent/CEventFactory_%%CODE%%.h";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mkevent/mkevent_factoryhead_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%EVENT%%/$code/g;
      $line =~ s/%%EVENTC%%/$code_cap/g;
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
  
  # Make the factory source file.
  print("Making factory source...\n");
  $filename = "output_mkevent/CEventFactory_%%CODE%%.cpp";
  $filename =~ s/%%CODE%%/$code/g;
	if(open(FILEIN,"<templates_mkevent/mkevent_factorybody_tmpl.txt") &&
     open(FILEOUT,">$filename"))
	{
    foreach $line (<FILEIN>)
    {
      $line =~ s/%%EVENT%%/$code/g;
      $line =~ s/%%EVENTC%%/$code_cap/g;
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
  
  print("Source code output to output_event directory.\n");