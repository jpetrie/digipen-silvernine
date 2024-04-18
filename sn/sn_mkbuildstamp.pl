
  print("Generating build identification information...\n");

  if(open(SVNENTRIES,"<.svn/entries"))
  {
    while (<SVNENTRIES>)
    {
	    if(m/committed-rev="(\d+)"/i)
	    {
		    $stamp_id = $1;
		    close(SVNENTRIES);
	    }
    }
  }

  # Open the files.
	if(open(BUILDSTAMPIN,"<sn_buildstampdefines.h") &&
     open(BUILDSTAMPOUT,">sn_buildstamp_temp.h"))
	{
    foreach $line (<BUILDSTAMPIN>)
    {
      # Echo from the input file to the temporary file.
      # When we find the build ID #define, write the real ID.
      if($line =~ m/#define SN_BUILDID/)
      {
        print(BUILDSTAMPOUT "#define SN_BUILDID     ","$stamp_id\n");
      }
      else
      {
        chomp($line);
        print(BUILDSTAMPOUT $line);
      }
    }

	}

  # Close the files.
	close(BUILDSTAMPIN);
	close(BUILDSTAMPOUT);

  # Copy scratch file over real file and delete.
  rename("sn_buildstamp_temp.h","sn_buildstampdefines.h");
