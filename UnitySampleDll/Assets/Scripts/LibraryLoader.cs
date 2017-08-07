using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Using IntPtr
using System;

// Using DllImport
using System.Runtime.InteropServices;

// Using Encoding
using System.Text;

public class LibraryLoader : MonoBehaviour {

    /**
     * Below are mapping to the dll export functions in the library
     */
    [DllImport("SampleCppDll")]
    private static extern IntPtr GetCustomString(byte[] charPtr, int length);

    [DllImport("SampleCppDll")]
    private static extern void DestroyString(IntPtr obj);

    [DllImport("SampleCppDll")]
    private static extern void GetString(IntPtr obj, byte[] buffer, int length);

    [DllImport("SampleCppDll")]
    private static extern int GetLength(IntPtr obj);

    [DllImport("SampleCppDll")]
    private static extern void Append(IntPtr obj, byte[] charPtr, int length);

    // Callback function definition
    private delegate void TextCallback(bool hasChanged, int newLength);

    [DllImport("SampleCppDll")]
    private static extern void SetCallback(IntPtr obj, TextCallback callback);
    
    // This holds the obj pointer for dll created object
    IntPtr customStrObj = IntPtr.Zero;

    void Awake () {
        // Use dll to create an instance object
        // string has to be passed using byte array with ascii encoding because c# is by default
        // double byte encoding
        byte[] myStringByte = Encoding.ASCII.GetBytes("Hello there");
        customStrObj = GetCustomString(myStringByte, myStringByte.Length);
        Debug.Log("customStrObj: " + customStrObj);

        // Use dll function to retreive data
        int myStringLength = GetLength(customStrObj);
        Debug.Log("customStrObj - myStringLength: " + myStringLength);

        // Use dll function to set data
        byte[] appendStringByte = Encoding.ASCII.GetBytes(", William");
        Append(customStrObj, appendStringByte, appendStringByte.Length);
        int appendStringLength = GetLength(customStrObj);
        Debug.Log("customStrObj - appendStringLength: " + appendStringLength);

        // Retreive data again to ensure set data works
        byte[] getAppendString = new byte[100];
        GetString(customStrObj, getAppendString, 100);
        Debug.Log("customStrObj - getAppendString: " + Encoding.ASCII.GetString(getAppendString));

        // Use dll export to set callback 
        SetCallback(customStrObj, (bool hasChanged, int newLength) => {
            Debug.Log("callback - hasChanged: " + hasChanged + ", newLength: " + newLength);
            byte[] callbackStr = new byte[100];
            GetString(customStrObj, callbackStr, 100);
            Debug.Log("callback - callbackStr: " + Encoding.ASCII.GetString(callbackStr));
            // Note that do not use function that will invoke callback inside callback!!!
        });

        // Let's see whether callback works or not
        byte[] appendStringByte2 = Encoding.ASCII.GetBytes(" and David");
        Append(customStrObj, appendStringByte2, appendStringByte2.Length);
    }

    void OnDestroy() {
        if(IntPtr.Zero != customStrObj) {
            // Destroy the object created by dll
            DestroyString(customStrObj);
            customStrObj = IntPtr.Zero;
        }
    }

}
