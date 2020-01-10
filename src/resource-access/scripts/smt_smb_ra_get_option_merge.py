#!/usr/bin/python
#
# smt_smb_ra_get_option_merge.py
#
# (C) Copyright IBM Corp. 2005
#
# THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
# ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
# CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
#
# You can obtain a current copy of the Eclipse Public License from
# http://www.opensource.org/licenses/eclipse-1.0.php
#
# Author:  Rodrigo Ceron <rceron@br.ibm.com>
#
# Contributors:
#
#####################################################################

from smt_smb_ra_parser import Parser
from sys import argv,exit
from os import write,close 
from smt_smb_ra_errors import *

try:
	filename = argv[1]
except IndexError:
	exit(EINVAL)
try:
	sharename = argv[2]
except IndexError:
	exit(EINVAL)
try:
	optname = argv[3]
except IndexError:
	exit(EINVAL)
try:	
	pipeid = int(argv[4])
except IndexError:
	exit(EINVAL)


try:
	p = Parser(filename)
except IOError:
	exit(ENOFILE)

opt = p.get_option_merge(sharename,optname)

if ((opt == ENOSHARE) or (opt == ENOOPT)):
	exit(opt) 


write(pipeid,opt + "\nSMBEOF\n")
close(pipeid);
