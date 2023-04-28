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

#include "EzGs2/Public/Version/Model/Gs2VersionEzVersion.h"

namespace Gs2::UE5::Version::Model
{

    TSharedPtr<FEzVersion> FEzVersion::WithMajor(
        const TOptional<int32> Major
    )
    {
        this->MajorValue = Major;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersion> FEzVersion::WithMinor(
        const TOptional<int32> Minor
    )
    {
        this->MinorValue = Minor;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersion> FEzVersion::WithMicro(
        const TOptional<int32> Micro
    )
    {
        this->MicroValue = Micro;
        return SharedThis(this);
    }
    TOptional<int32> FEzVersion::GetMajor() const
    {
        return MajorValue;
    }

    FString FEzVersion::GetMajorString() const
    {
        if (!MajorValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MajorValue.GetValue());
    }
    TOptional<int32> FEzVersion::GetMinor() const
    {
        return MinorValue;
    }

    FString FEzVersion::GetMinorString() const
    {
        if (!MinorValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinorValue.GetValue());
    }
    TOptional<int32> FEzVersion::GetMicro() const
    {
        return MicroValue;
    }

    FString FEzVersion::GetMicroString() const
    {
        if (!MicroValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MicroValue.GetValue());
    }

    Gs2::Version::Model::FVersionPtr FEzVersion::ToModel() const
    {
        return MakeShared<Gs2::Version::Model::FVersion>()
            ->WithMajor(MajorValue)
            ->WithMinor(MinorValue)
            ->WithMicro(MicroValue);
    }

    TSharedPtr<FEzVersion> FEzVersion::FromModel(const Gs2::Version::Model::FVersionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzVersion>()
            ->WithMajor(Model->GetMajor())
            ->WithMinor(Model->GetMinor())
            ->WithMicro(Model->GetMicro());
    }
}