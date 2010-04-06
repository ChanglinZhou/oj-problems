/*
 * Puzzle: http://www.hacker.org/coil/
 * Algorithm: Simple back-tracing algorithm.
 */

using System;
using System.Net;
using System.IO;
using System.Threading;
using System.Collections.Generic;

namespace HackerPuzzles
{

  class MortalCoilSolver
  {
    static int[,] offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    static char[] offNames = {'L', 'D', 'R', 'U'};
    Random rand = new Random();
    static string name, pw;
    int targetFill, boardX, boardY, startX = -1, startY = -1;
    int[,] board;
    string boardString, currentPath;
    int filledNumber, level;
    static string url = "http://www.hacker.org/coil/index.php?";

    static void Main(string[] args)
    {
      if (args.Length != 2)
      {
        Console.WriteLine("usage:\nMortalCoilSolver: Name and Pwd");
        return;
      }
      name = args[0]; pw = args[1];
      MortalCoilSolver mcs = new MortalCoilSolver();
      while (true) {
          mcs.go();
          Thread.Sleep(500);
      }
    }

    void go() {
      WebRequest request = WebRequest.Create(url + "name=" + name + 
                                             "&password=" + pw);
      WebResponse response = request.GetResponse();
      Stream inputStream = response.GetResponseStream();
      input2level(inputStream);
      Console.WriteLine(this);
      solve();
    }

    public override string ToString() {
      string s = "Level " + level + "(" + 
                 boardY + "x" + boardX + ") Starts:\n";
      for (int j = 0; j < boardY; j++) {
        for (int i = 0; i < boardX; i++)
        {
          s += board[i, j] > 0 ? 'X' : '.';
        }
        if (j < boardY - 1) s += '\n';
      }
      return s;
    }

    public bool solve() {
      System.DateTime start = System.DateTime.Now;
      string path = findSolutionPath();
      System.DateTime finish = System.DateTime.Now;
      System.TimeSpan delta = finish - start;
      Console.WriteLine("Solved at (" + startX + ", " + startY + ").");
      Console.WriteLine("Cost (" + delta.TotalSeconds + ").");
      Console.WriteLine("Path:(" + path + ").\n\n\n");
      WebRequest request = WebRequest.Create(url + "name=" + name + 
                                             "&password=" + pw + "&path=" + 
                                             path + "&x=" + startX + "&y=" + 
                                             startY);
      WebResponse response = request.GetResponse();
      Stream inputStream = response.GetResponseStream();
      StreamReader reader = new StreamReader(inputStream);
      while ((reader.ReadLine()) != null) { }
      inputStream.Close();
      return false;
    }

    int move(int x, int y, int dir)
    {
      int offx = offsets[dir, 0];
      int offy = offsets[dir, 1];
      int moveCount = 0;
      while(goodSquare(x + offx, y + offy)) {
        x += offx;
        y += offy;
        board[x, y] = 2;
        ++filledNumber;
        ++moveCount;
      }
      currentPath += offNames[dir];

      return moveCount;
    }

    void restore(int x, int y, int dir, int moveCount)
    {
      int offx = offsets[dir, 0];
      int offy = offsets[dir, 1];
      for (int i = 0; i < moveCount; ++i) {
        board[x, y] = 0;
        x += offx;
        y += offy;
      }
      currentPath = currentPath.Remove(currentPath.Length - 1);
      filledNumber -= moveCount;
    }

    void DFS(int x, int y)
    {
      if (filledNumber == targetFill) return;

      List<int> dirs = getSuggestedDirections(x, y);
      foreach (int dir in dirs) {
        int offx = offsets[dir, 0];
        int offy = offsets[dir, 1];
        if (goodSquare(x + offx, y + offy)) {
          int moveCount = move(x, y, dir);
          x += moveCount * offx;
          y += moveCount * offy;
          DFS(x, y);
          if (filledNumber == targetFill)
            break;
          restore(x, y, (dir + 2) % 4, moveCount);
          x -= moveCount * offx;
          y -= moveCount * offy;
        }
      }
    }

    struct Coordate {
      public int x;
      public int y;
    }

    string findSolutionPath()
    {
      for (int x = 0; x < boardX; ++x)
      {
        for (int y = 0; y < boardY; ++y)
        {
          if (goodSquare(x, y))
          {
            board[x, y] = 2;
            ++filledNumber;
            DFS(x, y);
            if (filledNumber == targetFill)
            {
              startX = x;
              startY = y;
              break;
            }
            board[x, y] = 0;
            --filledNumber;
          }
        }
        if (filledNumber == targetFill) break;
      }

      return currentPath;
    }

    bool goodSquare(int x, int y)
    {
        if (x < 0 || y < 0 || x >= boardX || y >= boardY) return false;
        return (board[x, y] == 0);
    }
   
    void input2level(Stream inputStream) {
      StreamReader reader = new StreamReader(inputStream);
      string line;
      while ((line = reader.ReadLine()) != null) {
        if (line.StartsWith("</tr></table>Level:")) {
          line = line.Split(':')[1].Trim();
          line = line.Split('<')[0];
          level = Int32.Parse(line);
          continue;
        }

        if (!line.StartsWith("\t\t\t<param name=\"FlashVars\"")) continue;
        char[] delimiterChars = { '\"' };
        // get just the value
        line = line.Split('\"')[3];
        delimiterChars = new char[]{ '(', '=', '|', '&', ')' };
        // split up the name value pairs
        string[] ss = line.Split(delimiterChars);
        boardX = Int32.Parse(ss[1]); boardY = Int32.Parse(ss[3]);
        board = new int[boardX, boardY];
        boardString = ss[5];
        parseBoardString();
      }
      reader.Close();
    }

    void parseBoardString() {
      int cnt = 0;
      for (int x = 0; x < boardX; x++)
          for (int y = 0; y < boardY; y++) {
              int a = boardString[x + y * boardX] == 'X' ? 1 : 0;
              board[x, y] = a;
              cnt += a;
          }
      // how many squares we need to fill
      targetFill = (boardX * boardY) - cnt;
      currentPath = "";
      filledNumber = 0;
    }

    int numOfAvalidNeighbor(int x, int y) {
      if (!goodSquare(x, y)) return -1;

      int count = 0;
      for (int dir = 0; dir < 4; ++dir) {
        if (goodSquare(x + offsets[dir, 0], y + offsets[dir, 1]))
          ++count;
      }

      return count;
    }

    List<int> getSuggestedDirections(int x, int y)
    {
      List<int> dirs = new List<int>();
      int[] numbers = new int[4];
      
      for (int dir = 0; dir < 4; ++dir) {
        numbers[dir] = numOfAvalidNeighbor(x + offsets[dir, 0], y + offsets[dir, 1]);
      }

      for (int dir = 0; dir < 4; ++dir)
      {
        if (numbers[dir] >= 0)
        {
          if (dirs.Count == 0)
            dirs.Add(dir);
          else
          {
            int i = dirs.Count - 1;
            while (i >= 0)
            {
              if (numbers[dir] >= numbers[i])
              {
                dirs.Insert(i + 1, dir);
                break;
              }
              --i;
            }
            if (i < 0)
              dirs.Insert(i + 1, dir);
          }
        }
      }

      return dirs;
    }
  }
}