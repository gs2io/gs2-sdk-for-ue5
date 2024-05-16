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

#include "Chat/Model/ScriptSetting.h"

namespace Gs2::Chat::Model
{
    FScriptSetting::FScriptSetting():
        TriggerScriptIdValue(TOptional<FString>()),
        DoneTriggerTargetTypeValue(TOptional<FString>()),
        DoneTriggerScriptIdValue(TOptional<FString>()),
        DoneTriggerQueueNamespaceIdValue(TOptional<FString>())
    {
    }

    FScriptSetting::FScriptSetting(
        const FScriptSetting& From
    ):
        TriggerScriptIdValue(From.TriggerScriptIdValue),
        DoneTriggerTargetTypeValue(From.DoneTriggerTargetTypeValue),
        DoneTriggerScriptIdValue(From.DoneTriggerScriptIdValue),
        DoneTriggerQueueNamespaceIdValue(From.DoneTriggerQueueNamespaceIdValue)
    {
    }

    TSharedPtr<FScriptSetting> FScriptSetting::WithTriggerScriptId(
        const TOptional<FString> TriggerScriptId
    )
    {
        this->TriggerScriptIdValue = TriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FScriptSetting> FScriptSetting::WithDoneTriggerTargetType(
        const TOptional<FString> DoneTriggerTargetType
    )
    {
        this->DoneTriggerTargetTypeValue = DoneTriggerTargetType;
        return SharedThis(this);
    }

    TSharedPtr<FScriptSetting> FScriptSetting::WithDoneTriggerScriptId(
        const TOptional<FString> DoneTriggerScriptId
    )
    {
        this->DoneTriggerScriptIdValue = DoneTriggerScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FScriptSetting> FScriptSetting::WithDoneTriggerQueueNamespaceId(
        const TOptional<FString> DoneTriggerQueueNamespaceId
    )
    {
        this->DoneTriggerQueueNamespaceIdValue = DoneTriggerQueueNamespaceId;
        return SharedThis(this);
    }
    TOptional<FString> FScriptSetting::GetTriggerScriptId() const
    {
        return TriggerScriptIdValue;
    }
    TOptional<FString> FScriptSetting::GetDoneTriggerTargetType() const
    {
        return DoneTriggerTargetTypeValue;
    }
    TOptional<FString> FScriptSetting::GetDoneTriggerScriptId() const
    {
        return DoneTriggerScriptIdValue;
    }
    TOptional<FString> FScriptSetting::GetDoneTriggerQueueNamespaceId() const
    {
        return DoneTriggerQueueNamespaceIdValue;
    }

    TSharedPtr<FScriptSetting> FScriptSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScriptSetting>()
            ->WithTriggerScriptId(Data->HasField(ANSI_TO_TCHAR("triggerScriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("triggerScriptId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDoneTriggerTargetType(Data->HasField(ANSI_TO_TCHAR("doneTriggerTargetType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("doneTriggerTargetType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDoneTriggerScriptId(Data->HasField(ANSI_TO_TCHAR("doneTriggerScriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("doneTriggerScriptId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDoneTriggerQueueNamespaceId(Data->HasField(ANSI_TO_TCHAR("doneTriggerQueueNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("doneTriggerQueueNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FScriptSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerScriptId", TriggerScriptIdValue.GetValue());
        }
        if (DoneTriggerTargetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("doneTriggerTargetType", DoneTriggerTargetTypeValue.GetValue());
        }
        if (DoneTriggerScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("doneTriggerScriptId", DoneTriggerScriptIdValue.GetValue());
        }
        if (DoneTriggerQueueNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("doneTriggerQueueNamespaceId", DoneTriggerQueueNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FScriptSetting::TypeName = "ScriptSetting";
}