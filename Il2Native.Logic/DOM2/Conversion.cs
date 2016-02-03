﻿namespace Il2Native.Logic.DOM2
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using Microsoft.CodeAnalysis;
    using Microsoft.CodeAnalysis.CSharp;
    using Microsoft.CodeAnalysis.CSharp.Symbols;

    public class Conversion : Expression
    {
        private TypeSymbol typeSource;

        private TypeSymbol typeDestination;

        private Expression operand;

        private ConversionKind conversionKind;

        internal void Parse(BoundConversion boundConversion)
        {
            base.Parse(boundConversion);
            this.typeSource = boundConversion.Operand.Type;
            this.typeDestination = boundConversion.Type;
            this.operand = Deserialize(boundConversion.Operand) as Expression;
            this.conversionKind = boundConversion.ConversionKind;
        }

        internal override void WriteTo(CCodeWriterBase c)
        {
            switch (this.conversionKind)
            {
                case ConversionKind.MethodGroup:
                    Debug.Assert(false, "Not Implemented");
                    ////throw new NotImplementedException();
                    return;
                case ConversionKind.NullToPointer:
                    // The null pointer is represented as 0u.
                    c.TextSpan("(uintptr_t)0");
                    return;
                case ConversionKind.Boxing:
                    c.TextSpan("__box<");
                    c.WriteTypeFullName(this.typeSource);
                    c.TextSpan(">");
                    break;
                case ConversionKind.Unboxing:
                    c.TextSpan("__unbox<");
                    c.WriteType(this.typeDestination);
                    c.TextSpan(",");
                    c.WhiteSpace();
                    c.WriteTypeFullName(this.typeDestination);
                    c.TextSpan(">");
                    break;
                case ConversionKind.ExplicitReference:
                case ConversionKind.ImplicitReference:

                    var useSiteDiagnostics = new HashSet<DiagnosticInfo>();
                    if (this.typeDestination.TypeKind != TypeKind.TypeParameter && this.typeSource.IsDerivedFrom(this.typeDestination, true, ref useSiteDiagnostics))
                    {
                        c.TextSpan("static_cast<");
                        c.WriteType(this.typeDestination);
                        c.TextSpan(">");
                    }
                    else
                    {
                        // TODO: finish dynamic cast
                        //c.TextSpan("dynamic_cast<");
                        if ((this.conversionKind == ConversionKind.ExplicitReference || this.conversionKind == ConversionKind.ImplicitReference)
                            && this.typeDestination.IsInterfaceType())
                        {
                            c.TextSpan("static_cast<");
                        }
                        else
                        {
                            c.TextSpan("reinterpret_cast<");
                        }
                        c.WriteType(this.typeDestination);
                        c.TextSpan(">");
                    }

                    break;
                case ConversionKind.PointerToInteger:
                case ConversionKind.IntegerToPointer:
                        c.TextSpan("reinterpret_cast<");
                        c.WriteType(this.typeDestination);
                        c.TextSpan(">");
                    break;
                default:
                    c.TextSpan("static_cast<");
                    c.WriteType(this.typeDestination);
                    c.TextSpan(">");
                    break;
            }

            c.TextSpan("(");

            // TODO: temp hack for supporting cast to interface
            if ((this.conversionKind == ConversionKind.ExplicitReference || this.conversionKind == ConversionKind.ImplicitReference)
                && this.typeDestination.IsInterfaceType())
            {
                c.TextSpan("nullptr/*");
                this.operand.WriteTo(c);
                c.TextSpan("*/");
            }
            else
            {
                this.operand.WriteTo(c);
            }

            c.TextSpan(")");
        }
    }
}
