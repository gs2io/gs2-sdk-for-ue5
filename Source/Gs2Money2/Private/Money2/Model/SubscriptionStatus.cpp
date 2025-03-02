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

#include "Money2/Model/SubscriptionStatus.h"

namespace Gs2::Money2::Model
{
    FSubscriptionStatus::FSubscriptionStatus():
        UserIdValue(TOptional<FString>()),
        ContentNameValue(TOptional<FString>()),
        StatusValue(TOptional<FString>()),
        ExpiresAtValue(TOptional<int64>()),
        DetailValue(nullptr)
    {
    }

    FSubscriptionStatus::FSubscriptionStatus(
        const FSubscriptionStatus& From
    ):
        UserIdValue(From.UserIdValue),
        ContentNameValue(From.ContentNameValue),
        StatusValue(From.StatusValue),
        ExpiresAtValue(From.ExpiresAtValue),
        DetailValue(From.DetailValue)
    {
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::WithDetail(
        const TSharedPtr<TArray<TSharedPtr<Model::FSubscribeTransaction>>> Detail
    )
    {
        this->DetailValue = Detail;
        return SharedThis(this);
    }
    TOptional<FString> FSubscriptionStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FSubscriptionStatus::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FSubscriptionStatus::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FSubscriptionStatus::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FSubscriptionStatus::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FSubscribeTransaction>>> FSubscriptionStatus::GetDetail() const
    {
        return DetailValue;
    }

    TSharedPtr<FSubscriptionStatus> FSubscriptionStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubscriptionStatus>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpiresAt(Data->HasField(ANSI_TO_TCHAR("expiresAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expiresAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithDetail(Data->HasField(ANSI_TO_TCHAR("detail")) ? [Data]() -> TSharedPtr<TArray<Model::FSubscribeTransactionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FSubscribeTransactionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("detail")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("detail")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("detail")))
                        {
                            v->Add(Model::FSubscribeTransaction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSubscribeTransactionPtr>>());
    }

    TSharedPtr<FJsonObject> FSubscriptionStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ContentNameValue.IsSet())
        {
            JsonRootObject->SetStringField("contentName", ContentNameValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (DetailValue != nullptr && DetailValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DetailValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("detail", v);
        }
        return JsonRootObject;
    }

    FString FSubscriptionStatus::TypeName = "SubscriptionStatus";
}