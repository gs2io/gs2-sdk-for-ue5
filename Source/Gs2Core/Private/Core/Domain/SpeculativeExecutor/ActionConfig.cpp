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

#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    FString EscapeJsonStringContent(const FString& Value)
    {
        FString Escaped;
        for (const TCHAR Character : Value)
        {
            switch (Character)
            {
            case TEXT('"'): Escaped += TEXT("\\\""); break;
            case TEXT('\\'): Escaped += TEXT("\\\\"); break;
            case TEXT('\b'): Escaped += TEXT("\\b"); break;
            case TEXT('\f'): Escaped += TEXT("\\f"); break;
            case TEXT('\n'): Escaped += TEXT("\\n"); break;
            case TEXT('\r'): Escaped += TEXT("\\r"); break;
            case TEXT('\t'): Escaped += TEXT("\\t"); break;
            default:
                if (static_cast<uint32>(Character) > 0xffff)
                {
                    const uint32 CodePoint = static_cast<uint32>(Character) - 0x10000;
                    Escaped += FString::Printf(TEXT("\\u%04x\\u%04x"),
                        0xd800 + (CodePoint >> 10), 0xdc00 + (CodePoint & 0x3ff));
                }
                else if (Character < 0x20 || Character > 0x7e)
                {
                    Escaped += FString::Printf(TEXT("\\u%04x"), static_cast<uint32>(Character));
                }
                else
                {
                    Escaped.AppendChar(Character);
                }
                break;
            }
        }
        return Escaped;
    }

    namespace
    {
        FString ActionConfigPlaceholder(const TOptional<FString>& Key)
        {
            return FString::Printf(TEXT("#{%s}"), *Key.Get(FString()));
        }
    }

    Gs2::Core::Model::FAcquireActionPtr ApplyConfig(
        const Gs2::Core::Model::FAcquireActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    )
    {
        if (!Action.IsValid() || !Action->GetRequest().IsSet() || !Value.IsSet()) return nullptr;
        return MakeShared<Gs2::Core::Model::FAcquireAction>(*Action)->WithRequest(
            Action->GetRequest().Get(FString()).Replace(
                *ActionConfigPlaceholder(Key), *EscapeJsonStringContent(Value.Get(FString()))));
    }

    Gs2::Core::Model::FConsumeActionPtr ApplyConfig(
        const Gs2::Core::Model::FConsumeActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    )
    {
        if (!Action.IsValid() || !Action->GetRequest().IsSet() || !Value.IsSet()) return nullptr;
        return MakeShared<Gs2::Core::Model::FConsumeAction>(*Action)->WithRequest(
            Action->GetRequest().Get(FString()).Replace(
                *ActionConfigPlaceholder(Key), *EscapeJsonStringContent(Value.Get(FString()))));
    }

    Gs2::Core::Model::FVerifyActionPtr ApplyConfig(
        const Gs2::Core::Model::FVerifyActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    )
    {
        if (!Action.IsValid() || !Action->GetRequest().IsSet() || !Value.IsSet()) return nullptr;
        return MakeShared<Gs2::Core::Model::FVerifyAction>(*Action)->WithRequest(
            Action->GetRequest().Get(FString()).Replace(
                *ActionConfigPlaceholder(Key), *EscapeJsonStringContent(Value.Get(FString()))));
    }
}
