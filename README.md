Workfunction
============

A C program to calculate a 1D planar averaged electrostatic potential from a 3D potential grid for the density functional theory code VASP. It can be used to compute the workfunction (or ionisation potential) for a material surface or as an alignment technique for comparing the electronic eigenvalues of different systems. 

For original Fortran version, search Github repository WMD-group/workfunction

Version
------------
Adapted from the program VTOTAV that was distributed with VASP 4 and is of uncertain origin.

V1 Fortran - Original distro version
V2 Fortran - Various updates from JLF Da Silva and A Walsh (2007-2009)
             http://people.bath.ac.uk/aw558 (a.walsh@bath.ac.uk)
V2 C       - Translated from V2 Fortran version by Shuhao Wu
             sw3023@columbia.edu

Reads in the 3D electrostatic potential (LOCPOT) from VASP which is generated with LVHAR= .TRUE. in the INCAR file.

Outputs the 1D potential averaged along one of the lattice vectors, which can be used, e.g., to compute the vacuum level.

Note: to obtain the Hartree + Exc contributions, the flag LVTOT = .TRUE. should be set instead. In VASP 4, this flag (confusingly) provided the Hatree contributions only.

To do
------------ 
1. Automatically align values using the calculated vacuum level.
2. Check if dipole corrections are required (slope of potential in the vacuum).
3. Change axis units to Angstrom (for all IDIR).
4. Update to read artbitrary number of ion types. 

Used in
------------
- "Structure, stability and work functions of the low index surfaces of pure indium oxide and Sn-doped indium oxide (ITO) from density functional theory" A. Walsh and C. R. A. Catlow, Journal of Materials Chemistry 20, 10438 (2010). DOI: 10.1039/C0JM01816C 
