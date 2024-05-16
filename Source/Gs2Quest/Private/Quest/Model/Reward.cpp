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

#include "Quest/Model/Reward.h"

namespace Gs2::Quest::Model
{
    FReward::FReward():
        ActionValue(TOptional<FString>()),
        RequestValue(TOptional<FString>()),
        ItemIdValue(TOptional<FString>()),
        ValueValue(TOptional<int32>())
    {
    }

    FReward::FReward(
        const FReward& From
    ):
        ActionValue(From.ActionValue),
        RequestValue(From.RequestValue),
        ItemIdValue(From.ItemIdValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FReward> FReward::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FReward> FReward::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }

    TSharedPtr<FReward> FReward::WithItemId(
        const TOptional<FString> ItemId
    )
    {
        this->ItemIdValue = ItemId;
        return SharedThis(this);
    }

    TSharedPtr<FReward> FReward::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FReward::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FReward::GetRequest() const
    {
        return RequestValue;
    }
    TOptional<FString> FReward::GetItemId() const
    {
        return ItemIdValue;
    }
    TOptional<int32> FReward::GetValue() const
    {
        return ValueValue;
    }

    FString FReward::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }

    TSharedPtr<FReward> FReward::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReward>()
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRequest(Data->HasField(ANSI_TO_TCHAR("request")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("request"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithItemId(Data->HasField(ANSI_TO_TCHAR("itemId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("itemId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FReward::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
        }
        if (RequestValue.IsSet())
        {
            JsonRootObject->SetStringField("request", RequestValue.GetValue());
        }
        if (ItemIdValue.IsSet())
        {
            JsonRootObject->SetStringField("itemId", ItemIdValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FReward::TypeName = "Reward";
}