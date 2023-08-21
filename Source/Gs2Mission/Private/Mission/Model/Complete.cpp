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

#include "Mission/Model/Complete.h"

namespace Gs2::Mission::Model
{
    FComplete::FComplete():
        CompleteIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        CompletedMissionTaskNamesValue(nullptr),
        ReceivedMissionTaskNamesValue(nullptr),
        NextResetAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FComplete::FComplete(
        const FComplete& From
    ):
        CompleteIdValue(From.CompleteIdValue),
        UserIdValue(From.UserIdValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        CompletedMissionTaskNamesValue(From.CompletedMissionTaskNamesValue),
        ReceivedMissionTaskNamesValue(From.ReceivedMissionTaskNamesValue),
        NextResetAtValue(From.NextResetAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FComplete> FComplete::WithCompleteId(
        const TOptional<FString> CompleteId
    )
    {
        this->CompleteIdValue = CompleteId;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithCompletedMissionTaskNames(
        const TSharedPtr<TArray<FString>> CompletedMissionTaskNames
    )
    {
        this->CompletedMissionTaskNamesValue = CompletedMissionTaskNames;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithReceivedMissionTaskNames(
        const TSharedPtr<TArray<FString>> ReceivedMissionTaskNames
    )
    {
        this->ReceivedMissionTaskNamesValue = ReceivedMissionTaskNames;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithNextResetAt(
        const TOptional<int64> NextResetAt
    )
    {
        this->NextResetAtValue = NextResetAt;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FComplete> FComplete::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FComplete::GetCompleteId() const
    {
        return CompleteIdValue;
    }
    TOptional<FString> FComplete::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FComplete::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }
    TSharedPtr<TArray<FString>> FComplete::GetCompletedMissionTaskNames() const
    {
        return CompletedMissionTaskNamesValue;
    }
    TSharedPtr<TArray<FString>> FComplete::GetReceivedMissionTaskNames() const
    {
        return ReceivedMissionTaskNamesValue;
    }
    TOptional<int64> FComplete::GetNextResetAt() const
    {
        return NextResetAtValue;
    }

    FString FComplete::GetNextResetAtString() const
    {
        if (!NextResetAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextResetAtValue.GetValue());
    }
    TOptional<int64> FComplete::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FComplete::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FComplete::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FComplete::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FComplete::GetRevision() const
    {
        return RevisionValue;
    }

    FString FComplete::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FComplete::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):group:(?<missionGroupName>.+):complete"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FComplete::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):group:(?<missionGroupName>.+):complete"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FComplete::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):group:(?<missionGroupName>.+):complete"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FComplete::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):group:(?<missionGroupName>.+):complete"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FComplete::GetMissionGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):user:(?<userId>.+):group:(?<missionGroupName>.+):complete"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FComplete> FComplete::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FComplete>()
            ->WithCompleteId(Data->HasField("completeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("completeId", v))
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
            ->WithMissionGroupName(Data->HasField("missionGroupName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("missionGroupName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCompletedMissionTaskNames(Data->HasField("completedMissionTaskNames") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("completedMissionTaskNames") && Data->HasTypedField<EJson::Array>("completedMissionTaskNames"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("completedMissionTaskNames"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithReceivedMissionTaskNames(Data->HasField("receivedMissionTaskNames") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("receivedMissionTaskNames") && Data->HasTypedField<EJson::Array>("receivedMissionTaskNames"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("receivedMissionTaskNames"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithNextResetAt(Data->HasField("nextResetAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("nextResetAt", v))
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
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FComplete::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CompleteIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeId", CompleteIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (MissionGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupName", MissionGroupNameValue.GetValue());
        }
        if (CompletedMissionTaskNamesValue != nullptr && CompletedMissionTaskNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CompletedMissionTaskNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("completedMissionTaskNames", v);
        }
        if (ReceivedMissionTaskNamesValue != nullptr && ReceivedMissionTaskNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReceivedMissionTaskNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("receivedMissionTaskNames", v);
        }
        if (NextResetAtValue.IsSet())
        {
            JsonRootObject->SetStringField("nextResetAt", FString::Printf(TEXT("%lld"), NextResetAtValue.GetValue()));
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

    FString FComplete::TypeName = "Complete";
}