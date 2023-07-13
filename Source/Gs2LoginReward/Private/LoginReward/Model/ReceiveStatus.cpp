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

#include "LoginReward/Model/ReceiveStatus.h"

namespace Gs2::LoginReward::Model
{
    FReceiveStatus::FReceiveStatus():
        ReceiveStatusIdValue(TOptional<FString>()),
        BonusModelNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ReceivedStepsValue(nullptr),
        LastReceivedAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FReceiveStatus::FReceiveStatus(
        const FReceiveStatus& From
    ):
        ReceiveStatusIdValue(From.ReceiveStatusIdValue),
        BonusModelNameValue(From.BonusModelNameValue),
        UserIdValue(From.UserIdValue),
        ReceivedStepsValue(From.ReceivedStepsValue),
        LastReceivedAtValue(From.LastReceivedAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithReceiveStatusId(
        const TOptional<FString> ReceiveStatusId
    )
    {
        this->ReceiveStatusIdValue = ReceiveStatusId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithBonusModelName(
        const TOptional<FString> BonusModelName
    )
    {
        this->BonusModelNameValue = BonusModelName;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithReceivedSteps(
        const TSharedPtr<TArray<bool>> ReceivedSteps
    )
    {
        this->ReceivedStepsValue = ReceivedSteps;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithLastReceivedAt(
        const TOptional<int64> LastReceivedAt
    )
    {
        this->LastReceivedAtValue = LastReceivedAt;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveStatus::GetReceiveStatusId() const
    {
        return ReceiveStatusIdValue;
    }
    TOptional<FString> FReceiveStatus::GetBonusModelName() const
    {
        return BonusModelNameValue;
    }
    TOptional<FString> FReceiveStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<TArray<bool>> FReceiveStatus::GetReceivedSteps() const
    {
        return ReceivedStepsValue;
    }
    TOptional<int64> FReceiveStatus::GetLastReceivedAt() const
    {
        return LastReceivedAtValue;
    }

    FString FReceiveStatus::GetLastReceivedAtString() const
    {
        if (!LastReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastReceivedAtValue.GetValue());
    }
    TOptional<int64> FReceiveStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FReceiveStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FReceiveStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FReceiveStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FReceiveStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):user:(?<userId>.+):status:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceiveStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):user:(?<userId>.+):status:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceiveStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):user:(?<userId>.+):status:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceiveStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):user:(?<userId>.+):status:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceiveStatus::GetBonusModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):loginReward:(?<namespaceName>.+):user:(?<userId>.+):status:(?<bonusModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FReceiveStatus> FReceiveStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveStatus>()
            ->WithReceiveStatusId(Data->HasField("receiveStatusId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("receiveStatusId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBonusModelName(Data->HasField("bonusModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("bonusModelName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReceivedSteps(Data->HasField("receivedSteps") ? [Data]() -> TSharedPtr<TArray<bool>>
                {
                    auto v = MakeShared<TArray<bool>>();
                    if (!Data->HasTypedField<EJson::Null>("receivedSteps") && Data->HasTypedField<EJson::Array>("receivedSteps"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("receivedSteps"))
                        {
                            v->Add(JsonObjectValue->AsBool());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<bool>>())
            ->WithLastReceivedAt(Data->HasField("lastReceivedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("lastReceivedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FReceiveStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ReceiveStatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField("receiveStatusId", ReceiveStatusIdValue.GetValue());
        }
        if (BonusModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("bonusModelName", BonusModelNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ReceivedStepsValue != nullptr && ReceivedStepsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReceivedStepsValue)
            {
                v.Add(MakeShared<FJsonValueBoolean>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("receivedSteps", v);
        }
        if (LastReceivedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("lastReceivedAt", FString::Printf(TEXT("%lld"), LastReceivedAtValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FReceiveStatus::TypeName = "ReceiveStatus";
}