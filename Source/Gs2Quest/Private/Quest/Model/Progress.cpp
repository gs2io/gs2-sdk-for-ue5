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

#include "Quest/Model/Progress.h"

namespace Gs2::Quest::Model
{
    FProgress::FProgress():
        ProgressIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        QuestModelIdValue(TOptional<FString>()),
        RandomSeedValue(TOptional<int64>()),
        RewardsValue(nullptr),
        MetadataValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FProgress::FProgress(
        const FProgress& From
    ):
        ProgressIdValue(From.ProgressIdValue),
        UserIdValue(From.UserIdValue),
        TransactionIdValue(From.TransactionIdValue),
        QuestModelIdValue(From.QuestModelIdValue),
        RandomSeedValue(From.RandomSeedValue),
        RewardsValue(From.RewardsValue),
        MetadataValue(From.MetadataValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FProgress> FProgress::WithProgressId(
        const TOptional<FString> ProgressId
    )
    {
        this->ProgressIdValue = ProgressId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithQuestModelId(
        const TOptional<FString> QuestModelId
    )
    {
        this->QuestModelIdValue = QuestModelId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FProgress::GetProgressId() const
    {
        return ProgressIdValue;
    }
    TOptional<FString> FProgress::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FProgress::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FProgress::GetQuestModelId() const
    {
        return QuestModelIdValue;
    }
    TOptional<int64> FProgress::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FProgress::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FProgress::GetRewards() const
    {
        return RewardsValue;
    }
    TOptional<FString> FProgress::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FProgress::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FProgress::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FProgress::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FProgress::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FProgress::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FProgress> FProgress::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FProgress>()
            ->WithProgressId(Data->HasField("progressId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("progressId", v))
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
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("transactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithQuestModelId(Data->HasField("questModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("questModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRandomSeed(Data->HasField("randomSeed") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("randomSeed", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRewards(Data->HasField("rewards") ? [Data]() -> TSharedPtr<TArray<Model::FRewardPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRewardPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("rewards") && Data->HasTypedField<EJson::Array>("rewards"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("rewards"))
                        {
                            v->Add(Model::FReward::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRewardPtr>>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FProgress::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProgressIdValue.IsSet())
        {
            JsonRootObject->SetStringField("progressId", ProgressIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (QuestModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("questModelId", QuestModelIdValue.GetValue());
        }
        if (RandomSeedValue.IsSet())
        {
            JsonRootObject->SetStringField("randomSeed", FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue()));
        }
        if (RewardsValue != nullptr && RewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("rewards", v);
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
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

    FString FProgress::TypeName = "Progress";
}