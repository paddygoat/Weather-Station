long z=-1;     // Used to count cycles and gets reset after successful call back from server recieving data.


void counter()
{
  if (z>5000000)            // This needs to be changed to reset z on successful call back from server.
  {
    z=0;
  }
}
