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

#include "MegaField/Model/Layer.h"

namespace Gs2::MegaField::Model
{
    FLayer::FLayer():
        LayerIdValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        NumberOfMinEntriesValue(TOptional<int32>()),
        NumberOfMaxEntriesValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FLayer::FLayer(
        const FLayer& From
    ):
        LayerIdValue(From.LayerIdValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        NumberOfMinEntriesValue(From.NumberOfMinEntriesValue),
        NumberOfMaxEntriesValue(From.NumberOfMaxEntriesValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FLayer> FLayer::WithLayerId(
        const TOptional<FString> LayerId
    )
    {
        this->LayerIdValue = LayerId;
        return SharedThis(this);
    }

    TSharedPtr<FLayer> FLayer::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FLayer> FLayer::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FLayer> FLayer::WithNumberOfMinEntries(
        const TOptional<int32> NumberOfMinEntries
    )
    {
        this->NumberOfMinEntriesValue = NumberOfMinEntries;
        return SharedThis(this);
    }

    TSharedPtr<FLayer> FLayer::WithNumberOfMaxEntries(
        const TOptional<int32> NumberOfMaxEntries
    )
    {
        this->NumberOfMaxEntriesValue = NumberOfMaxEntries;
        return SharedThis(this);
    }

    TSharedPtr<FLayer> FLayer::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FLayer::GetLayerId() const
    {
        return LayerIdValue;
    }
    TOptional<FString> FLayer::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }
    TOptional<FString> FLayer::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }
    TOptional<int32> FLayer::GetNumberOfMinEntries() const
    {
        return NumberOfMinEntriesValue;
    }

    FString FLayer::GetNumberOfMinEntriesString() const
    {
        if (!NumberOfMinEntriesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NumberOfMinEntriesValue.GetValue());
    }
    TOptional<int32> FLayer::GetNumberOfMaxEntries() const
    {
        return NumberOfMaxEntriesValue;
    }

    FString FLayer::GetNumberOfMaxEntriesString() const
    {
        if (!NumberOfMaxEntriesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NumberOfMaxEntriesValue.GetValue());
    }
    TOptional<int64> FLayer::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FLayer::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FLayer::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):layer:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLayer::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):layer:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLayer::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):layer:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLayer::GetAreaModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):layer:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLayer::GetLayerModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):layer:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FLayer> FLayer::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLayer>()
            ->WithLayerId(Data->HasField("layerId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("layerId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAreaModelName(Data->HasField("areaModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("areaModelName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLayerModelName(Data->HasField("layerModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("layerModelName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNumberOfMinEntries(Data->HasField("numberOfMinEntries") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("numberOfMinEntries", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithNumberOfMaxEntries(Data->HasField("numberOfMaxEntries") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("numberOfMaxEntries", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FLayer::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LayerIdValue.IsSet())
        {
            JsonRootObject->SetStringField("layerId", LayerIdValue.GetValue());
        }
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        if (NumberOfMinEntriesValue.IsSet())
        {
            JsonRootObject->SetNumberField("numberOfMinEntries", NumberOfMinEntriesValue.GetValue());
        }
        if (NumberOfMaxEntriesValue.IsSet())
        {
            JsonRootObject->SetNumberField("numberOfMaxEntries", NumberOfMaxEntriesValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FLayer::TypeName = "Layer";
}