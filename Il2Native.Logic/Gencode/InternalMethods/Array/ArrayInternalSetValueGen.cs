﻿namespace Il2Native.Logic.Gencode.InternalMethods
{
    using System;
    using System.Collections.Generic;
    using System.Linq;

    using PEAssemblyReader;
    using OpCodesEmit = System.Reflection.Emit.OpCodes;

    public static class ArrayInternalSetValueGen
    {
        public static readonly string Name = "Void System.Array.InternalSetValue(Void*, System.Object)";

        public static IEnumerable<Tuple<string, Func<IMethod, IMethod>>> Generate(ICodeWriter codeWriter)
        {

            var typedReferenceType = codeWriter.System.System_TypedReference;
            var intPtrType = codeWriter.System.System_IntPtr;

            var t1 =OpCodeExtensions.GetFieldByName(typedReferenceType, "Value", codeWriter);
            var t2 =OpCodeExtensions.GetFieldByName(typedReferenceType, "Type", codeWriter);
            var t3 =OpCodeExtensions.GetFieldByName(intPtrType, "m_value", codeWriter);
            var t4 =codeWriter.System.System_Object.ToPointerType();
            var t5 =codeWriter.System.System_Object;
            var t6 =codeWriter.System.System_Boolean;
            var t7 =codeWriter.System.System_Char;
            var t8 =codeWriter.System.System_SByte;
            var t9 =codeWriter.System.System_Byte;
            var t10 =codeWriter.System.System_Int16;
            var t11 =codeWriter.System.System_UInt16;
            var t12 =codeWriter.System.System_Int32;
            var t13 =codeWriter.System.System_UInt32;
            var t14 =codeWriter.System.System_Int64;
            var t15 =codeWriter.System.System_UInt64;
            var t16 =codeWriter.System.System_Single;
            var t17 =codeWriter.System.System_Double;
            var t18 =codeWriter.System.System_Decimal;
            var t19 =codeWriter.System.System_DateTime;
            var t20 = IlReader.Constructors(codeWriter.System.System_NotSupportedException, codeWriter).First(c => !c.GetParameters().Any());

            var codeList = new IlCodeBuilder();

            // get TypeCode of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t2);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.Add(Code.Conv_I4);

            // switch
            var @switch = codeList.Switch();

            // goto default case
            //var defaultCaseLabel1 = codeList.Branch(Code.Br, Code.Br_S);

            // TODO: do not support Structs for now
            var defaultCaseLabel1 = codeList.CreateLabel();
            codeList.New(t20);
            codeList.Add(Code.Throw);

            // case 0(TypeCode.Empty) -> Default
            @switch.Labels.Add(defaultCaseLabel1);

            // case 1(TypeCode.Object) -> Default
            @switch.Labels.Add(defaultCaseLabel1);

            // case 2(TypeCode.DBNull) -> Default
            @switch.Labels.Add(defaultCaseLabel1);

            // case 3(TypeCode.Boolean)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t6);
            codeList.Add(Code.Stind_I1);
            codeList.Add(Code.Ret);

            // case 4(TypeCode.Char)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t7);
            codeList.Add(Code.Stind_I2);
            codeList.Add(Code.Ret);

            // case 5(TypeCode.SByte)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t8);
            codeList.Add(Code.Stind_I1);
            codeList.Add(Code.Ret);

            // case 6(TypeCode.Byte)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t9);
            codeList.Add(Code.Stind_I1);
            codeList.Add(Code.Ret);

            // case 7(TypeCode.Int16)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t10);
            codeList.Add(Code.Stind_I2);
            codeList.Add(Code.Ret);

            // case 8(TypeCode.UInt16)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t11);
            codeList.Add(Code.Stind_I2);
            codeList.Add(Code.Ret);

            // case 9(TypeCode.Int32)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t12);
            codeList.Add(Code.Stind_I4);
            codeList.Add(Code.Ret);

            // case 10(TypeCode.UInt32)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t13);
            codeList.Add(Code.Stind_I4);
            codeList.Add(Code.Ret);

            // case 11(TypeCode.Int64)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t14);
            codeList.Add(Code.Stind_I8);
            codeList.Add(Code.Ret);

            // case 12(TypeCode.UInt64)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t15);
            codeList.Add(Code.Stind_I8);
            codeList.Add(Code.Ret);

            // case 13(TypeCode.Single)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t16);
            codeList.Add(Code.Stind_R4);
            codeList.Add(Code.Ret);

            // case 14(TypeCode.Double)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t17);
            codeList.Add(Code.Stind_R8);
            codeList.Add(Code.Ret);

            // case 15(TypeCode.Decimal)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t18);
            codeList.SaveObject(codeWriter.System.System_Decimal);
            codeList.Add(Code.Ret);

            // case 16(TypeCode.DateTime)
            @switch.Labels.Add(codeList.CreateLabel());
            // get Value of TypedReference
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.LoadArgument(1);
            codeList.Unbox(t19);
            codeList.SaveObject(codeWriter.System.System_DateTime);
            codeList.Add(Code.Ret);

            // case 17 -> Default
            @switch.Labels.Add(codeList.CreateLabel());
            // throw NotSupportedException
            codeList.New(t20);
            codeList.Add(Code.Throw);

            // case 18(TypeCode.String) -> Default
            @switch.Labels.Add(defaultCaseLabel1);

            // default:
            codeList.Add(defaultCaseLabel1);

            // get Value of TypedReference (default case)
            codeList.LoadArgument(0);
            codeList.LoadFieldAddress(t1);
            // IntPtr.m_value
            codeList.LoadField(t3);
            codeList.Castclass(t4);
            codeList.LoadArgument(1);
            codeList.Add(Code.Stind_Ref);
            codeList.Add(Code.Ret);

            var locals = new List<IType>();

            var parameters = new List<IParameter>();
            parameters.Add(codeWriter.System.System_Void.ToPointerType().ToParameter("ref"));
            parameters.Add(codeWriter.System.System_Object.ToParameter("obj"));

            yield return MethodBodyBank.Register(Name, codeList.GetCode(), codeList.TokenResolutions, locals, parameters);
        }
    }
}