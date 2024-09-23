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

#include "Idle/Model/Status.h"

namespace Gs2::Idle::Model
{
    FStatus::FStatus():
        StatusIdValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RandomSeedValue(TOptional<int64>()),
        IdleMinutesValue(TOptional<int32>()),
        NextRewardsAtValue(TOptional<int64>()),
        MaximumIdleMinutesValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FStatus::FStatus(
        const FStatus& From
    ):
        StatusIdValue(From.StatusIdValue),
        CategoryNameValue(From.CategoryNameValue),
        UserIdValue(From.UserIdValue),
        RandomSeedValue(From.RandomSeedValue),
        IdleMinutesValue(From.IdleMinutesValue),
        NextRewardsAtValue(From.NextRewardsAtValue),
        MaximumIdleMinutesValue(From.MaximumIdleMinutesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FStatus> FStatus::WithStatusId(
        const TOptional<FString> StatusId
    )
    {
        this->StatusIdValue = StatusId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithIdleMinutes(
        const TOptional<int32> IdleMinutes
    )
    {
        this->IdleMinutesValue = IdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithNextRewardsAt(
        const TOptional<int64> NextRewardsAt
    )
    {
        this->NextRewardsAtValue = NextRewardsAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithMaximumIdleMinutes(
        const TOptional<int32> MaximumIdleMinutes
    )
    {
        this->MaximumIdleMinutesValue = MaximumIdleMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FStatus::GetStatusId() const
    {
        return StatusIdValue;
    }
    TOptional<FString> FStatus::GetCategoryName() const
    {
        return CategoryNameValue;
    }
    TOptional<FString> FStatus::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FStatus::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FStatus::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }
    TOptional<int32> FStatus::GetIdleMinutes() const
    {
        return IdleMinutesValue;
    }

    FString FStatus::GetIdleMinutesString() const
    {
        if (!IdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IdleMinutesValue.GetValue());
    }
    TOptional<int64> FStatus::GetNextRewardsAt() const
    {
        return NextRewardsAtValue;
    }

    FString FStatus::GetNextRewardsAtString() const
    {
        if (!NextRewardsAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRewardsAtValue.GetValue());
    }
    TOptional<int32> FStatus::GetMaximumIdleMinutes() const
    {
        return MaximumIdleMinutesValue;
    }

    FString FStatus::GetMaximumIdleMinutesString() const
    {
        if (!MaximumIdleMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumIdleMinutesValue.GetValue());
    }
    TOptional<int64> FStatus::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FStatus::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FStatus::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FStatus::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FStatus::GetRevision() const
    {
        return RevisionValue;
    }

    FString FStatus::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FStatus::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FStatus::GetCategoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):idle:(?<namespaceName>.+):user:(?<userId>.+):categoryModel:(?<categoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FStatus> FStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStatus>()
            ->WithStatusId(Data->HasField(ANSI_TO_TCHAR("statusId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("statusId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCategoryName(Data->HasField(ANSI_TO_TCHAR("categoryName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRandomSeed(Data->HasField(ANSI_TO_TCHAR("randomSeed")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("randomSeed"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithIdleMinutes(Data->HasField(ANSI_TO_TCHAR("idleMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("idleMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithNextRewardsAt(Data->HasField(ANSI_TO_TCHAR("nextRewardsAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("nextRewardsAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaximumIdleMinutes(Data->HasField(ANSI_TO_TCHAR("maximumIdleMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumIdleMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StatusIdValue.IsSet())
        {
            JsonRootObject->SetStringField("statusId", StatusIdValue.GetValue());
        }
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RandomSeedValue.IsSet())
        {
            JsonRootObject->SetStringField("randomSeed", FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue()));
        }
        if (IdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("idleMinutes", IdleMinutesValue.GetValue());
        }
        if (NextRewardsAtValue.IsSet())
        {
            JsonRootObject->SetStringField("nextRewardsAt", FString::Printf(TEXT("%lld"), NextRewardsAtValue.GetValue()));
        }
        if (MaximumIdleMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumIdleMinutes", MaximumIdleMinutesValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FStatus::TypeName = "Status";
}