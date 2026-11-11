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

#include "Realtime/Model/ParticipantSetting.h"

namespace Gs2::Realtime::Model
{
    FParticipantSetting::FParticipantSetting():
        UserIdValue(TOptional<FString>()),
        ScriptIdValue(TOptional<FString>())
    {
    }

    FParticipantSetting::FParticipantSetting(
        const FParticipantSetting& From
    ):
        UserIdValue(From.UserIdValue),
        ScriptIdValue(From.ScriptIdValue)
    {
    }

    TSharedPtr<FParticipantSetting> FParticipantSetting::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FParticipantSetting> FParticipantSetting::WithScriptId(
        const TOptional<FString> ScriptId
    )
    {
        this->ScriptIdValue = ScriptId;
        return SharedThis(this);
    }
    TOptional<FString> FParticipantSetting::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FParticipantSetting::GetScriptId() const
    {
        return ScriptIdValue;
    }

    TSharedPtr<FParticipantSetting> FParticipantSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FParticipantSetting>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScriptId(Data->HasField(ANSI_TO_TCHAR("scriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scriptId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FParticipantSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (ScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("scriptId"), ScriptIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FParticipantSetting::TypeName = "ParticipantSetting";
}