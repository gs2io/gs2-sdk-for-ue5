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

#include "MegaField/Model/Spatial.h"

namespace Gs2::MegaField::Model
{
    FSpatial::FSpatial():
        SpatialIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        PositionValue(nullptr),
        VectorValue(nullptr),
        RValue(TOptional<float>()),
        LastSyncAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FSpatial::FSpatial(
        const FSpatial& From
    ):
        SpatialIdValue(From.SpatialIdValue),
        UserIdValue(From.UserIdValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        PositionValue(From.PositionValue),
        VectorValue(From.VectorValue),
        RValue(From.RValue),
        LastSyncAtValue(From.LastSyncAtValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FSpatial> FSpatial::WithSpatialId(
        const TOptional<FString> SpatialId
    )
    {
        this->SpatialIdValue = SpatialId;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithPosition(
        const TSharedPtr<FPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithVector(
        const TSharedPtr<FVector> Vector
    )
    {
        this->VectorValue = Vector;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithLastSyncAt(
        const TOptional<int64> LastSyncAt
    )
    {
        this->LastSyncAtValue = LastSyncAt;
        return SharedThis(this);
    }

    TSharedPtr<FSpatial> FSpatial::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FSpatial::GetSpatialId() const
    {
        return SpatialIdValue;
    }
    TOptional<FString> FSpatial::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FSpatial::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }
    TOptional<FString> FSpatial::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }
    TSharedPtr<FPosition> FSpatial::GetPosition() const
    {
        return PositionValue;
    }
    TSharedPtr<FVector> FSpatial::GetVector() const
    {
        return VectorValue;
    }
    TOptional<float> FSpatial::GetR() const
    {
        return RValue;
    }

    FString FSpatial::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }
    TOptional<int64> FSpatial::GetLastSyncAt() const
    {
        return LastSyncAtValue;
    }

    FString FSpatial::GetLastSyncAtString() const
    {
        if (!LastSyncAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastSyncAtValue.GetValue());
    }
    TOptional<int64> FSpatial::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSpatial::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FSpatial::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSpatial::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSpatial::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSpatial::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSpatial::GetAreaModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSpatial::GetLayerModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):user:(?<userId>.+):spatial:(?<areaModelName>.+):(?<layerModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSpatial> FSpatial::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSpatial>()
            ->WithSpatialId(Data->HasField(ANSI_TO_TCHAR("spatialId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("spatialId"), v))
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
            ->WithAreaModelName(Data->HasField(ANSI_TO_TCHAR("areaModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("areaModelName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLayerModelName(Data->HasField(ANSI_TO_TCHAR("layerModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("layerModelName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPosition(Data->HasField(ANSI_TO_TCHAR("position")) ? [Data]() -> Model::FPositionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("position")))
                    {
                        return nullptr;
                    }
                    return Model::FPosition::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("position")));
                 }() : nullptr)
            ->WithVector(Data->HasField(ANSI_TO_TCHAR("vector")) ? [Data]() -> Model::FVectorPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("vector")))
                    {
                        return nullptr;
                    }
                    return Model::FVector::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("vector")));
                 }() : nullptr)
            ->WithR(Data->HasField(ANSI_TO_TCHAR("r")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("r"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithLastSyncAt(Data->HasField(ANSI_TO_TCHAR("lastSyncAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lastSyncAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FSpatial::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SpatialIdValue.IsSet())
        {
            JsonRootObject->SetStringField("spatialId", SpatialIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        if (PositionValue != nullptr && PositionValue.IsValid())
        {
            JsonRootObject->SetObjectField("position", PositionValue->ToJson());
        }
        if (VectorValue != nullptr && VectorValue.IsValid())
        {
            JsonRootObject->SetObjectField("vector", VectorValue->ToJson());
        }
        if (RValue.IsSet())
        {
            JsonRootObject->SetNumberField("r", RValue.GetValue());
        }
        if (LastSyncAtValue.IsSet())
        {
            JsonRootObject->SetStringField("lastSyncAt", FString::Printf(TEXT("%lld"), LastSyncAtValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSpatial::TypeName = "Spatial";
}