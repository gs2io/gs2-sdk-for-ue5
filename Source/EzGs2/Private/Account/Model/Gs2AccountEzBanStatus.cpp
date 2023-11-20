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

#include "Account/Model/Gs2AccountEzBanStatus.h"

namespace Gs2::UE5::Account::Model
{

    TSharedPtr<FEzBanStatus> FEzBanStatus::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBanStatus> FEzBanStatus::WithReason(
        const TOptional<FString> Reason
    )
    {
        this->ReasonValue = Reason;
        return SharedThis(this);
    }

    TSharedPtr<FEzBanStatus> FEzBanStatus::WithReleaseTimestamp(
        const TOptional<int64> ReleaseTimestamp
    )
    {
        this->ReleaseTimestampValue = ReleaseTimestamp;
        return SharedThis(this);
    }
    TOptional<FString> FEzBanStatus::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzBanStatus::GetReason() const
    {
        return ReasonValue;
    }
    TOptional<int64> FEzBanStatus::GetReleaseTimestamp() const
    {
        return ReleaseTimestampValue;
    }

    FString FEzBanStatus::GetReleaseTimestampString() const
    {
        if (!ReleaseTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReleaseTimestampValue.GetValue());
    }

    Gs2::Account::Model::FBanStatusPtr FEzBanStatus::ToModel() const
    {
        return MakeShared<Gs2::Account::Model::FBanStatus>()
            ->WithName(NameValue)
            ->WithReason(ReasonValue)
            ->WithReleaseTimestamp(ReleaseTimestampValue);
    }

    TSharedPtr<FEzBanStatus> FEzBanStatus::FromModel(const Gs2::Account::Model::FBanStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBanStatus>()
            ->WithName(Model->GetName())
            ->WithReason(Model->GetReason())
            ->WithReleaseTimestamp(Model->GetReleaseTimestamp());
    }
}