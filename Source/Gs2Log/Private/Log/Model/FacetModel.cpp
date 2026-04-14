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

#include "Log/Model/FacetModel.h"

namespace Gs2::Log::Model
{
    FFacetModel::FFacetModel():
        FacetModelIdValue(TOptional<FString>()),
        FieldValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        OrderValue(TOptional<int32>())
    {
    }

    FFacetModel::FFacetModel(
        const FFacetModel& From
    ):
        FacetModelIdValue(From.FacetModelIdValue),
        FieldValue(From.FieldValue),
        TypeValue(From.TypeValue),
        DisplayNameValue(From.DisplayNameValue),
        OrderValue(From.OrderValue)
    {
    }

    TSharedPtr<FFacetModel> FFacetModel::WithFacetModelId(
        const TOptional<FString> FacetModelId
    )
    {
        this->FacetModelIdValue = FacetModelId;
        return SharedThis(this);
    }

    TSharedPtr<FFacetModel> FFacetModel::WithField(
        const TOptional<FString> Field
    )
    {
        this->FieldValue = Field;
        return SharedThis(this);
    }

    TSharedPtr<FFacetModel> FFacetModel::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FFacetModel> FFacetModel::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FFacetModel> FFacetModel::WithOrder(
        const TOptional<int32> Order
    )
    {
        this->OrderValue = Order;
        return SharedThis(this);
    }
    TOptional<FString> FFacetModel::GetFacetModelId() const
    {
        return FacetModelIdValue;
    }
    TOptional<FString> FFacetModel::GetField() const
    {
        return FieldValue;
    }
    TOptional<FString> FFacetModel::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FFacetModel::GetDisplayName() const
    {
        return DisplayNameValue;
    }
    TOptional<int32> FFacetModel::GetOrder() const
    {
        return OrderValue;
    }

    FString FFacetModel::GetOrderString() const
    {
        if (!OrderValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), OrderValue.GetValue());
    }

    TOptional<FString> FFacetModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):model:facet:(?<field>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFacetModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):model:facet:(?<field>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFacetModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):model:facet:(?<field>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FFacetModel::GetFieldFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):log:(?<namespaceName>.+):model:facet:(?<field>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FFacetModel> FFacetModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFacetModel>()
            ->WithFacetModelId(Data->HasField(ANSI_TO_TCHAR("facetModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("facetModelId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithField(Data->HasField(ANSI_TO_TCHAR("field")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("field"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDisplayName(Data->HasField(ANSI_TO_TCHAR("displayName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithOrder(Data->HasField(ANSI_TO_TCHAR("order")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("order"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FFacetModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (FacetModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("facetModelId", FacetModelIdValue.GetValue());
        }
        if (FieldValue.IsSet())
        {
            JsonRootObject->SetStringField("field", FieldValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (OrderValue.IsSet())
        {
            JsonRootObject->SetNumberField("order", OrderValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FFacetModel::TypeName = "FacetModel";
}