﻿// --------------------------------------------------------------------------------------------------------------------
// <copyright file="ICodeWriter.cs" company="">
//   
// </copyright>
// <summary>
//   
// </summary>
// --------------------------------------------------------------------------------------------------------------------
namespace Il2Native.Logic
{
    using Il2Native.Logic.CodeParts;

    using PEAssemblyReader;
    using System.Collections.Generic;

    /// <summary>
    /// </summary>
    public interface ICodeWriter
    {
        /// <summary>
        /// </summary>
        void Close();

        /// <summary>
        /// </summary>
        /// <param name="value">
        /// </param>
        void DisableWrite(bool value);

        /// <summary>
        /// </summary>
        /// <param name="rawText">
        /// </param>
        void Write(string rawText);

        /// <summary>
        /// </summary>
        /// <param name="ilCode">
        /// </param>
        void Write(OpCodePart ilCode);

        /// <summary>
        /// </summary>
        void WriteAfterConstructors();

        /// <summary>
        /// </summary>
        /// <param name="count">
        /// </param>
        /// <param name="disablePostDeclarations">
        /// </param>
        void WriteAfterFields(int count);

        /// <summary>
        /// </summary>
        void WriteAfterMethods();

        void WritePostDeclarations(IType type);

        /// <summary>
        /// </summary>
        void WriteBeforeConstructors();

        /// <summary>
        /// </summary>
        /// <param name="count">
        /// </param>
        void WriteBeforeFields(int count);

        /// <summary>
        /// </summary>
        void WriteBeforeMethods();

        /// <summary>
        /// </summary>
        /// <param name="ctor">
        /// </param>
        /// <param name="genericContext">
        /// </param>
        void WriteConstructorEnd(IConstructor ctor, IGenericContext genericContext);

        /// <summary>
        /// </summary>
        /// <param name="ctor">
        /// </param>
        /// <param name="genericContext">
        /// </param>
        void WriteConstructorStart(IConstructor ctor, IGenericContext genericContext);

        /// <summary>
        /// </summary>
        void WriteEnd();

        /// <summary>
        /// </summary>
        /// <param name="field">
        /// </param>
        /// <param name="number">
        /// </param>
        /// <param name="count">
        /// </param>
        void WriteFieldEnd(IField field, int number, int count);

        /// <summary>
        /// </summary>
        /// <param name="field">
        /// </param>
        /// <param name="number">
        /// </param>
        /// <param name="count">
        /// </param>
        void WriteFieldStart(IField field, int number, int count);

        /// <summary>
        /// </summary>
        /// <param name="fieldType">
        /// </param>
        void WriteFieldType(IType fieldType);

        /// <summary>
        /// </summary>
        /// <param name="type">
        /// </param>
        /// <param name="number">
        /// </param>
        /// <param name="count">
        /// </param>
        void WriteForwardDeclaration(IType type, int number, int count);

        /// <summary>
        /// </summary>
        /// <param name="method">
        /// </param>
        /// <param name="genericContext">
        /// </param>
        void WriteMethodEnd(IMethod method, IGenericContext genericContext);

        /// <summary>
        /// </summary>
        /// <param name="method">
        /// </param>
        /// <param name="genericContext">
        /// </param>
        void WriteMethodStart(IMethod method, IGenericContext genericContext);

        /// <summary>
        /// </summary>
        void WriteRequiredTypesForBody();

        /// <summary>
        /// </summary>
        /// <param name="moduleName">
        /// </param>
        /// <param name="assemblyName">
        /// </param>
        /// ///
        void WriteStart(string moduleName, string assemblyName, bool isCoreLib, IEnumerable<string> allReference);

        /// <summary>
        /// </summary>
        void WriteStoredText();

        /// <summary>
        /// </summary>
        /// <param name="type">
        /// </param>
        void WriteTypeEnd(IType type);

        /// <summary>
        /// </summary>
        /// <param name="type">
        /// </param>
        /// <param name="genericContext">
        /// </param>
        void WriteTypeStart(IType type, IGenericContext genericContext);

        /// <summary>
        /// </summary>
        /// <param name="type">
        /// </param>
        bool IsProcessed(IType type);

        /// <summary>
        /// </summary>
        /// <param name="type">
        /// </param>
        bool IsPostDeclarationsProcessed(IType type);
    }
}