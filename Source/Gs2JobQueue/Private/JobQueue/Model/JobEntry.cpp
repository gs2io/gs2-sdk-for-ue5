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

#include "JobQueue/Model/JobEntry.h"

namespace Gs2::JobQueue::Model
{
    FJobEntry::FJobEntry():
        ScriptIdValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        MaxTryCountValue(TOptional<int32>())
    {
    }

    FJobEntry::FJobEntry(
        const FJobEntry& From
    ):
        ScriptIdValue(From.ScriptIdValue),
        ArgsValue(From.ArgsValue),
        MaxTryCountValue(From.MaxTryCountValue)
    {
    }

    TSharedPtr<FJobEntry> FJobEntry::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FJobEntry> FJobEntry::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FJobEntry> FJobEntry::WithMaxTryCount(
        const TOptional<int32> MaxTryCount
    )
    {
        this->MaxTryCountValue = MaxTryCount;
        return SharedThis(this);
    }
    TOptional<FString> FJobEntry::GetScriptId() const
    {
        return ScriptIdValue;
    }
    TOptional<FString> FJobEntry::GetArgs() const
    {
        return ArgsValue;
    }
    TOptional<int32> FJobEntry::GetMaxTryCount() const
    {
        return MaxTryCountValue;
    }

    FString FJobEntry::GetMaxTryCountString() const
    {
        if (!MaxTryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxTryCountValue.GetValue());
    }

    TSharedPtr<FJobEntry> FJobEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJobEntry>()
            ->WithScriptId(Data->HasField("scriptId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scriptId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithArgs(Data->HasField("args") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("args", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaxTryCount(Data->HasField("maxTryCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maxTryCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FJobEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scriptId", ScriptIdValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        if (MaxTryCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxTryCount", MaxTryCountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FJobEntry::TypeName = "JobEntry";
}