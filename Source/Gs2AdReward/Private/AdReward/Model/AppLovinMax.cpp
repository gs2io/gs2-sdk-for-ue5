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

#include "AdReward/Model/AppLovinMax.h"

namespace Gs2::AdReward::Model
{
    FAppLovinMax::FAppLovinMax():
        AllowAdUnitIdValue(TOptional<FString>()),
        EventKeyValue(TOptional<FString>())
    {
    }

    FAppLovinMax::FAppLovinMax(
        const FAppLovinMax& From
    ):
        AllowAdUnitIdValue(From.AllowAdUnitIdValue),
        EventKeyValue(From.EventKeyValue)
    {
    }

    TSharedPtr<FAppLovinMax> FAppLovinMax::WithAllowAdUnitId(
        const TOptional<FString> AllowAdUnitId
    )
    {
        this->AllowAdUnitIdValue = AllowAdUnitId;
        return SharedThis(this);
    }

    TSharedPtr<FAppLovinMax> FAppLovinMax::WithEventKey(
        const TOptional<FString> EventKey
    )
    {
        this->EventKeyValue = EventKey;
        return SharedThis(this);
    }
    TOptional<FString> FAppLovinMax::GetAllowAdUnitId() const
    {
        return AllowAdUnitIdValue;
    }
    TOptional<FString> FAppLovinMax::GetEventKey() const
    {
        return EventKeyValue;
    }

    TSharedPtr<FAppLovinMax> FAppLovinMax::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAppLovinMax>()
            ->WithAllowAdUnitId(Data->HasField(ANSI_TO_TCHAR("allowAdUnitId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("allowAdUnitId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEventKey(Data->HasField(ANSI_TO_TCHAR("eventKey")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventKey"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAppLovinMax::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AllowAdUnitIdValue.IsSet())
        {
            JsonRootObject->SetStringField("allowAdUnitId", AllowAdUnitIdValue.GetValue());
        }
        if (EventKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("eventKey", EventKeyValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAppLovinMax::TypeName = "AppLovinMax";
}