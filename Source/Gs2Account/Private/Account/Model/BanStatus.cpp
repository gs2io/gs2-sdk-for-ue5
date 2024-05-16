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

#include "Account/Model/BanStatus.h"

namespace Gs2::Account::Model
{
    FBanStatus::FBanStatus():
        NameValue(TOptional<FString>()),
        ReasonValue(TOptional<FString>()),
        ReleaseTimestampValue(TOptional<int64>())
    {
    }

    FBanStatus::FBanStatus(
        const FBanStatus& From
    ):
        NameValue(From.NameValue),
        ReasonValue(From.ReasonValue),
        ReleaseTimestampValue(From.ReleaseTimestampValue)
    {
    }

    TSharedPtr<FBanStatus> FBanStatus::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBanStatus> FBanStatus::WithReason(
        const TOptional<FString> Reason
    )
    {
        this->ReasonValue = Reason;
        return SharedThis(this);
    }

    TSharedPtr<FBanStatus> FBanStatus::WithReleaseTimestamp(
        const TOptional<int64> ReleaseTimestamp
    )
    {
        this->ReleaseTimestampValue = ReleaseTimestamp;
        return SharedThis(this);
    }
    TOptional<FString> FBanStatus::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBanStatus::GetReason() const
    {
        return ReasonValue;
    }
    TOptional<int64> FBanStatus::GetReleaseTimestamp() const
    {
        return ReleaseTimestampValue;
    }

    FString FBanStatus::GetReleaseTimestampString() const
    {
        if (!ReleaseTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ReleaseTimestampValue.GetValue());
    }

    TSharedPtr<FBanStatus> FBanStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBanStatus>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReason(Data->HasField(ANSI_TO_TCHAR("reason")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("reason"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReleaseTimestamp(Data->HasField(ANSI_TO_TCHAR("releaseTimestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("releaseTimestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FBanStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ReasonValue.IsSet())
        {
            JsonRootObject->SetStringField("reason", ReasonValue.GetValue());
        }
        if (ReleaseTimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("releaseTimestamp", FString::Printf(TEXT("%lld"), ReleaseTimestampValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FBanStatus::TypeName = "BanStatus";
}