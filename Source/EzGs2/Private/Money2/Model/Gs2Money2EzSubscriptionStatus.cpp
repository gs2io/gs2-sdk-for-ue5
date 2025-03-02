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

#include "Money2/Model/Gs2Money2EzSubscriptionStatus.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::WithDetail(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>>> Detail
    )
    {
        this->DetailValue = Detail;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscriptionStatus::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FEzSubscriptionStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSubscriptionStatus::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FEzSubscriptionStatus::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzSubscriptionStatus::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzSubscribeTransaction>>> FEzSubscriptionStatus::GetDetail() const
    {
        return DetailValue;
    }

    Gs2::Money2::Model::FSubscriptionStatusPtr FEzSubscriptionStatus::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FSubscriptionStatus>()
            ->WithContentName(ContentNameValue)
            ->WithUserId(UserIdValue)
            ->WithStatus(StatusValue)
            ->WithExpiresAt(ExpiresAtValue)
            ->WithDetail([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Money2::Model::FSubscribeTransaction>>>();
                    if (DetailValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *DetailValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzSubscriptionStatus> FEzSubscriptionStatus::FromModel(const Gs2::Money2::Model::FSubscriptionStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscriptionStatus>()
            ->WithContentName(Model->GetContentName())
            ->WithUserId(Model->GetUserId())
            ->WithStatus(Model->GetStatus())
            ->WithExpiresAt(Model->GetExpiresAt())
            ->WithDetail([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzSubscribeTransaction>>>();
                    if (Model->GetDetail() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetDetail())
                    {
                        v->Add(FEzSubscribeTransaction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}