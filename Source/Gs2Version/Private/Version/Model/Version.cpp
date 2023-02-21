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

#include "Version/Model/Version.h"

namespace Gs2::Version::Model
{
    FVersion::FVersion():
        MajorValue(TOptional<int32>()),
        MinorValue(TOptional<int32>()),
        MicroValue(TOptional<int32>())
    {
    }

    FVersion::FVersion(
        const FVersion& From
    ):
        MajorValue(From.MajorValue),
        MinorValue(From.MinorValue),
        MicroValue(From.MicroValue)
    {
    }

    TSharedPtr<FVersion> FVersion::WithMajor(
        const TOptional<int32> Major
    )
    {
        this->MajorValue = Major;
        return SharedThis(this);
    }

    TSharedPtr<FVersion> FVersion::WithMinor(
        const TOptional<int32> Minor
    )
    {
        this->MinorValue = Minor;
        return SharedThis(this);
    }

    TSharedPtr<FVersion> FVersion::WithMicro(
        const TOptional<int32> Micro
    )
    {
        this->MicroValue = Micro;
        return SharedThis(this);
    }
    TOptional<int32> FVersion::GetMajor() const
    {
        return MajorValue;
    }

    FString FVersion::GetMajorString() const
    {
        if (!MajorValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MajorValue.GetValue());
    }
    TOptional<int32> FVersion::GetMinor() const
    {
        return MinorValue;
    }

    FString FVersion::GetMinorString() const
    {
        if (!MinorValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MinorValue.GetValue());
    }
    TOptional<int32> FVersion::GetMicro() const
    {
        return MicroValue;
    }

    FString FVersion::GetMicroString() const
    {
        if (!MicroValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MicroValue.GetValue());
    }

    TSharedPtr<FVersion> FVersion::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVersion>()
            ->WithMajor(Data->HasField("major") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("major", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMinor(Data->HasField("minor") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("minor", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMicro(Data->HasField("micro") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("micro", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FVersion::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MajorValue.IsSet())
        {
            JsonRootObject->SetNumberField("major", MajorValue.GetValue());
        }
        if (MinorValue.IsSet())
        {
            JsonRootObject->SetNumberField("minor", MinorValue.GetValue());
        }
        if (MicroValue.IsSet())
        {
            JsonRootObject->SetNumberField("micro", MicroValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FVersion::TypeName = "Version";
}