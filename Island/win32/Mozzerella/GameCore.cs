﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Mozzerella
{
    class GameCore
    {
        [DllImport("Island.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int OpenWindow();

        [DllImport("Island.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int CloseWindow();

        [DllImport("Island.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Update();

        [DllImport("Island.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int ChangeTool(int tool);
    }
}
