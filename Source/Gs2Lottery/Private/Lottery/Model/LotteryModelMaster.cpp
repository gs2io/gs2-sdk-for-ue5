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

#include "Lottery/Model/LotteryModelMaster.h"

namespace Gs2::Lottery::Model
{
    FLotteryModelMaster::FLotteryModelMaster():
        LotteryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        ChoicePrizeTableScriptIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FLotteryModelMaster::FLotteryModelMaster(
        const FLotteryModelMaster& From
    ):
        LotteryModelIdValue(From.LotteryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        ModeValue(From.ModeValue),
        MethodValue(From.MethodValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        ChoicePrizeTableScriptIdValue(From.ChoicePrizeTableScriptIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithLotteryModelId(
        const TOptional<FString> LotteryModelId
    )
    {
        this->LotteryModelIdValue = LotteryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithChoicePrizeTableScriptId(
        const TOptional<FString> ChoicePrizeTableScriptId
    )
    {
        this->ChoicePrizeTableScriptIdValue = ChoicePrizeTableScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FLotteryModelMaster::GetLotteryModelId() const
    {
        return LotteryModelIdValue;
    }
    TOptional<FString> FLotteryModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FLotteryModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FLotteryModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FLotteryModelMaster::GetMode() const
    {
        return ModeValue;
    }
    TOptional<FString> FLotteryModelMaster::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FLotteryModelMaster::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }
    TOptional<FString> FLotteryModelMaster::GetChoicePrizeTableScriptId() const
    {
        return ChoicePrizeTableScriptIdValue;
    }
    TOptional<int64> FLotteryModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FLotteryModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FLotteryModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FLotteryModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FLotteryModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):lotteryModel:(?<lotteryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLotteryModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):lotteryModel:(?<lotteryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLotteryModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):lotteryModel:(?<lotteryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLotteryModelMaster::GetLotteryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):lotteryModel:(?<lotteryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FLotteryModelMaster> FLotteryModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLotteryModelMaster>()
            ->WithLotteryModelId(Data->HasField("lotteryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("lotteryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMode(Data->HasField("mode") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("mode", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMethod(Data->HasField("method") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("method", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeTableName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithChoicePrizeTableScriptId(Data->HasField("choicePrizeTableScriptId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("choicePrizeTableScriptId", v))
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

    TSharedPtr<FJsonObject> FLotteryModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LotteryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("lotteryModelId", LotteryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ModeValue.IsSet())
        {
            JsonRootObject->SetStringField("mode", ModeValue.GetValue());
        }
        if (MethodValue.IsSet())
        {
            JsonRootObject->SetStringField("method", MethodValue.GetValue());
        }
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (ChoicePrizeTableScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("choicePrizeTableScriptId", ChoicePrizeTableScriptIdValue.GetValue());
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

    FString FLotteryModelMaster::TypeName = "LotteryModelMaster";
}