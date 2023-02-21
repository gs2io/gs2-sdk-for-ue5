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

#include "Quest/Model/CompletedQuestList.h"

namespace Gs2::Quest::Model
{
    FCompletedQuestList::FCompletedQuestList():
        CompletedQuestListIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        CompleteQuestNamesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FCompletedQuestList::FCompletedQuestList(
        const FCompletedQuestList& From
    ):
        CompletedQuestListIdValue(From.CompletedQuestListIdValue),
        UserIdValue(From.UserIdValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        CompleteQuestNamesValue(From.CompleteQuestNamesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithCompletedQuestListId(
        const TOptional<FString> CompletedQuestListId
    )
    {
        this->CompletedQuestListIdValue = CompletedQuestListId;
        return SharedThis(this);
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithCompleteQuestNames(
        const TSharedPtr<TArray<FString>> CompleteQuestNames
    )
    {
        this->CompleteQuestNamesValue = CompleteQuestNames;
        return SharedThis(this);
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FCompletedQuestList::GetCompletedQuestListId() const
    {
        return CompletedQuestListIdValue;
    }
    TOptional<FString> FCompletedQuestList::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FCompletedQuestList::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }
    TSharedPtr<TArray<FString>> FCompletedQuestList::GetCompleteQuestNames() const
    {
        return CompleteQuestNamesValue;
    }
    TOptional<int64> FCompletedQuestList::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FCompletedQuestList::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FCompletedQuestList::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FCompletedQuestList::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FCompletedQuestList::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):completed:group:(?<questGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCompletedQuestList::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):completed:group:(?<questGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCompletedQuestList::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):completed:group:(?<questGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCompletedQuestList::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):completed:group:(?<questGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCompletedQuestList::GetQuestGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):completed:group:(?<questGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCompletedQuestList> FCompletedQuestList::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCompletedQuestList>()
            ->WithCompletedQuestListId(Data->HasField("completedQuestListId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("completedQuestListId", v))
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
            ->WithQuestGroupName(Data->HasField("questGroupName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("questGroupName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCompleteQuestNames(Data->HasField("completeQuestNames") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("completeQuestNames") && Data->HasTypedField<EJson::Array>("completeQuestNames"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("completeQuestNames"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FCompletedQuestList::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CompletedQuestListIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completedQuestListId", CompletedQuestListIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (QuestGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("questGroupName", QuestGroupNameValue.GetValue());
        }
        if (CompleteQuestNamesValue != nullptr && CompleteQuestNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CompleteQuestNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("completeQuestNames", v);
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

    FString FCompletedQuestList::TypeName = "CompletedQuestList";
}