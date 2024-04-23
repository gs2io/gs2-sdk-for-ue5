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

#include "Inventory/Model/ReferenceOf.h"

namespace Gs2::Inventory::Model
{
    FReferenceOf::FReferenceOf():
        ReferenceOfIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>())
    {
    }

    FReferenceOf::FReferenceOf(
        const FReferenceOf& From
    ):
        ReferenceOfIdValue(From.ReferenceOfIdValue),
        NameValue(From.NameValue)
    {
    }

    TSharedPtr<FReferenceOf> FReferenceOf::WithReferenceOfId(
        const TOptional<FString> ReferenceOfId
    )
    {
        this->ReferenceOfIdValue = ReferenceOfId;
        return SharedThis(this);
    }

    TSharedPtr<FReferenceOf> FReferenceOf::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }
    TOptional<FString> FReferenceOf::GetReferenceOfId() const
    {
        return ReferenceOfIdValue;
    }
    TOptional<FString> FReferenceOf::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FReferenceOf::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetItemNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetItemSetNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(7);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReferenceOf::GetReferenceOfFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+):item:(?<itemName>.+):itemSet:(?<itemSetName>.+):referenceOf:(?<referenceOf>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(8);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FReferenceOf> FReferenceOf::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReferenceOf>()
            ->WithReferenceOfId(Data->HasField("referenceOfId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("referenceOfId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FReferenceOf::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ReferenceOfIdValue.IsSet())
        {
            JsonRootObject->SetStringField("referenceOfId", ReferenceOfIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FReferenceOf::TypeName = "ReferenceOf";
}