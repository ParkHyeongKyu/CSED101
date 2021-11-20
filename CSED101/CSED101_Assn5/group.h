#ifndef GROUP_H
#define GROUP_H

void add_node(LIST **plist, NODE *temp);
void remove_node(LIST **plist, NODE *fi, int gn);
void play(FILE *infile, LIST **plist);
#endif