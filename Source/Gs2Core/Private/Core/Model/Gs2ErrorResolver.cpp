/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Core/Model/Gs2ErrorResolver.h"

#include "Misc/ScopeLock.h"

namespace Gs2::Core::Model
{
    namespace
    {
        FCriticalSection& ResolversLock()
        {
            static FCriticalSection Lock;
            return Lock;
        }

        TMap<FString, FGs2ServiceErrorResolver>& Resolvers()
        {
            static TMap<FString, FGs2ServiceErrorResolver> Map;
            return Map;
        }

        FString ToPascalCase(const TArray<FString>& Words, const int32 Begin, const int32 End)
        {
            FString Result;
            for (int32 Index = Begin; Index < End; ++Index)
            {
                Result += Words[Index].Left(1).ToUpper() + Words[Index].Mid(1);
            }
            return Result;
        }
    }

    bool FGs2ErrorResolver::Register(const FString& Service, FGs2ServiceErrorResolver Resolver)
    {
        FScopeLock Lock(&ResolversLock());
        Resolvers().Add(Service, MoveTemp(Resolver));
        return true;
    }

    FGs2ErrorPtr FGs2ErrorResolver::Resolve(const FString& Service, const FString& Method, FGs2ErrorPtr Error)
    {
        if (!Error.IsValid())
        {
            return Error;
        }
        FGs2ServiceErrorResolver Resolver;
        {
            FScopeLock Lock(&ResolversLock());
            if (const auto Found = Resolvers().Find(Service))
            {
                Resolver = *Found;
            }
        }
        if (!Resolver)
        {
            return Error;
        }
        return Resolver(Method, Error);
    }

    FGs2ErrorPtr FGs2ErrorResolver::ResolveAction(const FString& Action, FGs2ErrorPtr Error)
    {
        FString Service;
        FString Method;
        if (!Action.Split(TEXT(":"), &Service, &Method) || Service.IsEmpty() || Method.IsEmpty())
        {
            return Error;
        }
        return Resolve(Service, Method, Error);
    }

    FGs2ErrorPtr FGs2ErrorResolver::ResolveJobScript(const FString& ScriptId, FGs2ErrorPtr Error)
    {
        FString ScriptName = ScriptId;
        int32 Separator;
        if (ScriptId.FindLastChar(TEXT(':'), Separator))
        {
            ScriptName = ScriptId.Mid(Separator + 1);
        }
        const FString Prefix = TEXT("execute_");
        if (!ScriptName.StartsWith(Prefix, ESearchCase::CaseSensitive))
        {
            return Error;
        }
        TArray<FString> Words;
        ScriptName.Mid(Prefix.Len()).ParseIntoArray(Words, TEXT("_"), true);
        for (int32 Index = 1; Index < Words.Num(); ++Index)
        {
            const FString Service = TEXT("Gs2") + ToPascalCase(Words, 0, Index);
            bool bRegistered;
            {
                FScopeLock Lock(&ResolversLock());
                bRegistered = Resolvers().Contains(Service);
            }
            if (bRegistered)
            {
                return Resolve(
                    Service,
                    ToPascalCase(Words, Index, Words.Num()),
                    Error
                );
            }
        }
        return Error;
    }

    bool FGs2ErrorResolver::HasCode(const FGs2ErrorPtr& Error, const FString& Code)
    {
        if (!Error.IsValid() || !Error->GetErrors().IsValid())
        {
            return false;
        }
        for (const auto& Detail : *Error->GetErrors())
        {
            if (Detail.IsValid() && Detail->Code().Equals(Code, ESearchCase::CaseSensitive))
            {
                return true;
            }
        }
        return false;
    }
}
