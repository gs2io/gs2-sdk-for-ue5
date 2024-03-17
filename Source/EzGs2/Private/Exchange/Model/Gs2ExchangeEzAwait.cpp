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

#include "Exchange/Model/Gs2ExchangeEzAwait.h"

namespace Gs2::UE5::Exchange::Model
{

    TSharedPtr<FEzAwait> FEzAwait::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithSkipSeconds(
        const TOptional<int32> SkipSeconds
    )
    {
        this->SkipSecondsValue = SkipSeconds;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithExchangedAt(
        const TOptional<int64> ExchangedAt
    )
    {
        this->ExchangedAtValue = ExchangedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzAwait> FEzAwait::WithAcquirableAt(
        const TOptional<int64> AcquirableAt
    )
    {
        this->AcquirableAtValue = AcquirableAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzAwait::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzAwait::GetRateName() const
    {
        return RateNameValue;
    }
    TOptional<FString> FEzAwait::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FEzAwait::GetSkipSeconds() const
    {
        return SkipSecondsValue;
    }

    FString FEzAwait::GetSkipSecondsString() const
    {
        if (!SkipSecondsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SkipSecondsValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> FEzAwait::GetConfig() const
    {
        return ConfigValue;
    }
    TOptional<int64> FEzAwait::GetExchangedAt() const
    {
        return ExchangedAtValue;
    }

    FString FEzAwait::GetExchangedAtString() const
    {
        if (!ExchangedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExchangedAtValue.GetValue());
    }
    TOptional<int64> FEzAwait::GetAcquirableAt() const
    {
        return AcquirableAtValue;
    }

    FString FEzAwait::GetAcquirableAtString() const
    {
        if (!AcquirableAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AcquirableAtValue.GetValue());
    }

    Gs2::Exchange::Model::FAwaitPtr FEzAwait::ToModel() const
    {
        return MakeShared<Gs2::Exchange::Model::FAwait>()
            ->WithUserId(UserIdValue)
            ->WithRateName(RateNameValue)
            ->WithName(NameValue)
            ->WithSkipSeconds(SkipSecondsValue)
            ->WithConfig([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Exchange::Model::FConfig>>>();
                    if (ConfigValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConfigValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithExchangedAt(ExchangedAtValue)
            ->WithAcquirableAt(AcquirableAtValue);
    }

    TSharedPtr<FEzAwait> FEzAwait::FromModel(const Gs2::Exchange::Model::FAwaitPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAwait>()
            ->WithUserId(Model->GetUserId())
            ->WithRateName(Model->GetRateName())
            ->WithName(Model->GetName())
            ->WithSkipSeconds(Model->GetSkipSeconds())
            ->WithConfig([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConfig>>>();
                    if (Model->GetConfig() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConfig())
                    {
                        v->Add(FEzConfig::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithExchangedAt(Model->GetExchangedAt())
            ->WithAcquirableAt(Model->GetAcquirableAt());
    }
}