Overview
--------
The famiy module allows you to display family trees on your Drupal website.

Users of your website can be given ownership of banners, and be allowed to
modify certain settings and view statistics.

Requirements
------------
Drupal 6.x

Features
--------
   * Import from GEDCOM files - almost ready
   * Editing capabilities for individual data, groups data (relationships) and locations 
   * Individual nodes showing full information on individual: Name, Birth/Death dates and places, parents, spouses, children
   * Group nodes showing full information on relationships: Relationship type, Marriage/Death dates and places, parents and children
   * Location nodes showing full information on location: Building, Street, City, County, State, Country
   * Full linking to other individuals
   * Biography may be added to each individual
   * Listing of all individuals, groups and locations
   * Ancestory and Descendary trees for all inidividuals

Installation
------------
Install files in modules folder and enable it in admin/modules.
Set access in admin/access control
Import GEDCOM file from your favorite genealogy software (admin/content/family_import).

Bugs and Suggestions
--------------------
 - Family website: http://drupal.org/project/family
 - Maintainer:  Jeremy Trojan

Planned features (please tell us what is useful to you)
-------------------------------------------------------
 - Source nodes (file/book, document, personal evidence, etc.)
 - Other nodes, based on GEDCOM record types: Header, Multimedia, Repository, Submitter.
 - Generating reports/trees.
 - Revisions control - users add or change data, while admin/editor can approve or deny changes.
 - GEDCOM import merge - update data from GEDCOM file to current database
 - GEDCOM export
 - Automatic names linking filter - link names in non family nodes to the individual page.
 - Advanced search (e.g. born in Atlantis, bet. 3000 to 4000 b.c.)
 - statistics (e.g. mean lifespan, number of individuals, ...)
 - events calendar (birthdays, events anniversaries)
 - relationship calculator (find the relationship of x to y)
 - Link to individuals on other family tree websites
 - Check for errors
 - Dates conversion (Gregorian, Hebrew, Muslim, ...)
