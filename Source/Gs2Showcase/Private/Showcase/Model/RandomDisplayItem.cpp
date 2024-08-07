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

#include "Showcase/Model/RandomDisplayItem.h"

namespace Gs2::Showcase::Model
{
    FRandomDisplayItem::FRandomDisplayItem():
        ShowcaseNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        VerifyActionsValue(nullptr),
        ConsumeActionsValue(nullptr),
        AcquireActionsValue(nullptr),
        CurrentPurchaseCountValue(TOptional<int32>()),
        MaximumPurchaseCountValue(TOptional<int32>())
    {
    }

    FRandomDisplayItem::FRandomDisplayItem(
        const FRandomDisplayItem& From
    ):
        ShowcaseNameValue(From.ShowcaseNameValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        VerifyActionsValue(From.VerifyActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue),
        AcquireActionsValue(From.AcquireActionsValue),
        CurrentPurchaseCountValue(From.CurrentPurchaseCountValue),
        MaximumPurchaseCountValue(From.MaximumPurchaseCountValue)
    {
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithCurrentPurchaseCount(
        const TOptional<int32> CurrentPurchaseCount
    )
    {
        this->CurrentPurchaseCountValue = CurrentPurchaseCount;
        return SharedThis(this);
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::WithMaximumPurchaseCount(
        const TOptional<int32> MaximumPurchaseCount
    )
    {
        this->MaximumPurchaseCountValue = MaximumPurchaseCount;
        return SharedThis(this);
    }
    TOptional<FString> FRandomDisplayItem::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }
    TOptional<FString> FRandomDisplayItem::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRandomDisplayItem::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FRandomDisplayItem::GetVerifyActions() const
    {
        return VerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FRandomDisplayItem::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FRandomDisplayItem::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int32> FRandomDisplayItem::GetCurrentPurchaseCount() const
    {
        return CurrentPurchaseCountValue;
    }

    FString FRandomDisplayItem::GetCurrentPurchaseCountString() const
    {
        if (!CurrentPurchaseCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentPurchaseCountValue.GetValue());
    }
    TOptional<int32> FRandomDisplayItem::GetMaximumPurchaseCount() const
    {
        return MaximumPurchaseCountValue;
    }

    FString FRandomDisplayItem::GetMaximumPurchaseCountString() const
    {
        if (!MaximumPurchaseCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumPurchaseCountValue.GetValue());
    }

    TSharedPtr<FRandomDisplayItem> FRandomDisplayItem::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRandomDisplayItem>()
            ->WithShowcaseName(Data->HasField(ANSI_TO_TCHAR("showcaseName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("showcaseName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVerifyActions(Data->HasField(ANSI_TO_TCHAR("verifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyActions")))
                        {
                            v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
            ->WithConsumeActions(Data->HasField(ANSI_TO_TCHAR("consumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeActions")))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithCurrentPurchaseCount(Data->HasField(ANSI_TO_TCHAR("currentPurchaseCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentPurchaseCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaximumPurchaseCount(Data->HasField(ANSI_TO_TCHAR("maximumPurchaseCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumPurchaseCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FRandomDisplayItem::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ShowcaseNameValue.IsSet())
        {
            JsonRootObject->SetStringField("showcaseName", ShowcaseNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (VerifyActionsValue != nullptr && VerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyActions", v);
        }
        if (ConsumeActionsValue != nullptr && ConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeActions", v);
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        if (CurrentPurchaseCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("currentPurchaseCount", CurrentPurchaseCountValue.GetValue());
        }
        if (MaximumPurchaseCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumPurchaseCount", MaximumPurchaseCountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRandomDisplayItem::TypeName = "RandomDisplayItem";
}