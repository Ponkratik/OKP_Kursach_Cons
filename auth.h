#pragma once
#ifndef AUTH_H
#define AUTH_H

int Loginning();
bool Registration();
int Authorisation();
void Verification();
void Ban(unsigned int);
void GiveAdmin(unsigned int);
void ShowAdmins();
void ShowUsers();
void DeleteAccount();

#endif