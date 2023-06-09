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

#include "Idle/Model/AcquireAction.h"

namespace Gs2::Idle::Model
{
    FAcquireAction::FAcquireAction():
        ActionValue(TOptional<FString>()),
        RequestValue(TOptional<FString>())
    {
    }

    FAcquireAction::FAcquireAction(
        const FAcquireAction& From
    ):
        ActionValue(From.ActionValue),
        RequestValue(From.RequestValue)
    {
    }

    TSharedPtr<FAcquireAction> FAcquireAction::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireAction> FAcquireAction::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }
    TOptional<FString> FAcquireAction::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FAcquireAction::GetRequest() const
    {
        return RequestValue;
    }

    TSharedPtr<FAcquireAction> FAcquireAction::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireAction>()
            ->WithAction(Data->HasField("action") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("action", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRequest(Data->HasField("request") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("request", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAcquireAction::ToJson() const
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
        return JsonRootObject;
    }

    FString FAcquireAction::TypeName = "AcquireAction";
}