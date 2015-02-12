#!/usr/bin/env python3
########################################
########################################
##
##  \file build.py
##  \brief Python build script.
##  \author J. Caleb Wherry
##
########################################
########################################


#
# Global imports:
#
import string, subprocess
from time import time
from colorama import init, Fore
from sys import exit


#
# Global start time:
#
startTime = time()


#
# Print log to stdout:
#
def displayLog(log):

  print('')
  print(Fore.MAGENTA + '#############################')
  print(Fore.MAGENTA + 'Dumping log file: ' + log.name)
  print(Fore.MAGENTA + '#############################')
  print('')

  # Open file and print it to stdout:
  with open(log.name, 'r') as fin:
    print(fin.read())

  print('')
  print(Fore.MAGENTA + '#############################')
  print(Fore.MAGENTA + 'End log dump.')
  print(Fore.MAGENTA + '#############################')
  print('')



#
# Verify number of processors:
#
def verifyNumProcessors(numProcs):

	# If numProcs is anything but an int greater than 0, hard-code a value of 1:
	#	NOTE: 
	#		The try-catch is here in case the numProcs passed in is something that
	#		is not castable to an int. The case I am specicially worried about is if
	#		something like "4 processors found" is returned. Hopefully this won't 
	#		happen but in the case that it does I catch and set the default.
	try:
		if int(numProcs) < 1:
			numProcs = "1"
	except:
		print(Fore.RED + "\t" + 'WARNING -- Number of processors could not be found, defaulting to 1!')
		numProcs = "1"
	
	# Return (maybe new) number of processors:
	return numProcs



#
# Execute system call:
#
def sysCall(cmds, log, pad="\t", shellExec=False):

  # Print command and run:
  print(pad + "Running '" + " ".join(cmds) + "'...", end=' ')
  returnCode = subprocess.call(cmds, shell=shellExec, stdout=log, stderr=subprocess.STDOUT)
  
  if returnCode != 0:
    print(Fore.RED + 'ERROR!!! Please see log output below!')
    displayLog(log)
    completeScript(1)
  print(Fore.GREEN + 'done!')



#
# Complete script:
#
def completeScript(exitCode=0):

  # Elapsed time:
  endTime = time()
  elapsedTime = endTime - startTime
  totalHours = int(elapsedTime / 3600)
  totalMinutes = int(elapsedTime / 60)
  totalSeconds = elapsedTime % 60

  # Display execution time:
  print('Execution time: {:d} hours, {:d} minutes, and {:.4f} seconds.'.format(totalHours, totalMinutes, totalSeconds) )
  print('')

  # Build script completion output:
  if exitCode == 0:
    print(Fore.GREEN + 'Build completed successfully: {:d}.'.format(exitCode))
  else:
    print(Fore.RED + 'Build completed UNsuccessfully: {:d}.'.format(exitCode))
  print('')

  # Exit:
  exit(exitCode)



#
# UNIX build:
#
def unixBuild(log, args):

  print('')
  print('UNIX build starting...')

  # Number of processors for parallel build:
  numProcs = str(args.num_procs);

  # Check numProcs, if 0 get number of processors from machine:
  if numProcs == "0":
    # Command to find number of processors (decode output to str then remove all whitespace):
    numProcs = subprocess.Popen(["cat /proc/cpuinfo | grep processor | wc -l"], shell=True, stdout=subprocess.PIPE).communicate()[0].decode("utf-8")
    numProcs = "".join(numProcs.split())

  # Verify number of processors:
  numProcs = verifyNumProcessors(numProcs)

  # Execute build commands:
  sysCall(["make", "-j"+numProcs], log)
  #sysCall(["make", "-j"+numProcs, "test"], log)
  #sysCall(["make", "-j"+numProcs, "doc"], log)
  #sysCall(["make", "-j"+numProcs, "install"], log)

  print('UNIX build complete!')
  print('')



#
# Windows build:
#
def windowsBuild(log, args):

  print('')
  print('Windows build starting...')

  # Number of processors for parallel build:
  numProcs = str(args.num_procs)

  # Check numProcs, if 0 get number of processors from machine:
  if numProcs == "0":
    # Command to find number of processors (decode output to str then remove all whitespace):
    numProcs = subprocess.Popen(["echo %NUMBER_OF_PROCESSORS%"], shell=True, stdout=subprocess.PIPE).communicate()[0].decode("utf-8")
    numProcs = "".join(numProcs.split())

  # Verify number of processors:
  numProcs = verifyNumProcessors(numProcs)

  # TODO: Figure out how to deal with build targets on windows.

  # Execute build commands:
  sysCall(["msbuild", "ALL_BUILD.vcxproj"], log)
  #sysCall(["msbuild", "RUN_TESTS.vcxproj"], log)
  #sysCall(["msbuild", "ZERO_CHECK.vcxproj"], log)
  #sysCall(["msbuild", "INSTALL.vcxproj"], log)

  print('Windows build complete!')
  print('')



#
# Main function:
#
if __name__ == "__main__":

  # Imports:
  import argparse
  from sys import argv
  from os import path, getcwd, mkdir, chdir
  from platform import system
  from datetime import datetime
  from shutil import rmtree
  from glob import glob


  #
  # Argument parsing:
  #
  parser = argparse.ArgumentParser()
  parser.add_argument("-b", "--build-type", help="Build type (default: Debug).", choices=["Debug","Release"], default="Debug")
  parser.add_argument("-c", "--clean", help="Remove all build directories in current working directory matching 'local-build_*' and exit.", action="store_true")
  parser.add_argument("-i", "--install-prefix", help="Prefix for the install directory.", type=str, default="")
  parser.add_argument("-j", "--num-procs", help="Number of processors for parallel builds (default: number of processors on machine)", type=int, default=0)
  parser.add_argument("-l", "--log-display", help="Display build log to stdout.", action="store_true")
  parser.add_argument("-s", "--static-libs", help="Build static instead of shared libraries.", action="store_true")
  args = parser.parse_args()


  #
  # Init colorama:
  #
  init(autoreset=True)


  #
  # Build script init output:
  #
  print('')
  print(Fore.GREEN + '######################')
  print(Fore.GREEN + 'Automated Build Script')
  print(Fore.GREEN + '######################')
  print('')


  #
  # Remove build directories if clean specified:
  #
  if args.clean:
    print("Removing all build directories matching 'build/':")
    buildDirs = glob('build/')
    buildDirs = filter(path.isdir, buildDirs)
    for dir in buildDirs:
      print(Fore.RED + "\t" + dir)
      rmtree(dir)
    print(Fore.GREEN + 'done!')
    print('')
    completeScript()


  # Get timestamp:
  timeStamp = datetime.fromtimestamp(time()).strftime('%Y-%m-%d_%H-%M-%S')

  # Get current path:
  currentPath = path.abspath(getcwd())

  # Get script path:
  # NOTE: 
  #   This SHOULD be cross-platform but some people say it isn't because of 
  #   the argv... I have yet to come across a situation where this fails so 
  #   I'm leaving it. I believe when it fails is if you have this in a module 
  #   therefore there is no argv define. However, in this case, this script 
  #   will always be run from the commnad line so we should not run into any 
  #   issues.
  scriptPath = path.abspath(path.dirname(argv[0]))

  # Get OS:
  localOS = system()

  # Create build directories:
  buildRoot = path.join(currentPath, 'build-'+args.build_type.lower())
  buildDir = path.join(buildRoot, 'build-files')
  mkdir(buildRoot)
  mkdir(buildDir)

  # Diplay build directory to screen:
  print('Build location: ' + Fore.MAGENTA + buildRoot + "\n")

  # Create install directory if prefix was not supplied:
  if args.install_prefix == "":
    installDir = path.join(buildRoot, 'install-files')
    mkdir(installDir)
  else:
    installDir = path.join(args.install_prefix)

  # Set library build type:
  if args.static_libs:
    sharedLibs = "OFF"
  else:
    sharedLibs = "ON"

  # Move into build directory:
  chdir(buildDir)

  # Create logfile:
  logFile = path.join(buildRoot, 'build.log')
  log = open(logFile, 'w');

  # On all platforms, we at least have to run cmake first to get build files:
  sysCall(
    ["cmake", scriptPath, 
     "-DCMAKE_INSTALL_PREFIX='" + installDir + "'", 
     "-DCMAKE_BUILD_TYPE=" + args.build_type,
     "-DBUILD_SHARED_LIBS=" + sharedLibs
    ], log, "")

  # Execute build based on platform from this point on:
  if localOS == 'Linux' or localOS == 'Darwin':
    unixBuild(log, args)
  elif localOS == 'Windows':
    windowsBuild(log, args)
  else:
    print(Fore.RED + '**ERROR**: OS platform "' + localOS + '" not recognized; aborting!')
    completeScript(1)

  # Display log if cmd argument set:
  if args.log_display:
    displayLog(log)

  # Close log file:
  log.close()

  # Go back to script location:
  chdir(scriptPath)
 
  #
  # Exit cleanly
  #
  completeScript()
