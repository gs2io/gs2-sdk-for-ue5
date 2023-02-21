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

#pragma once

#include "CoreMinimal.h"
#include "Version/Model/Version.h"

namespace Gs2::UE5::Version::Model
{
	class EZGS2_API FEzVersion final : public TSharedFromThis<FEzVersion>
	{
        TOptional<int32> MajorValue;
        TOptional<int32> MinorValue;
        TOptional<int32> MicroValue;

	public:
        TSharedPtr<FEzVersion> WithMajor(const TOptional<int32> Major);
        TSharedPtr<FEzVersion> WithMinor(const TOptional<int32> Minor);
        TSharedPtr<FEzVersion> WithMicro(const TOptional<int32> Micro);

        TOptional<int32> GetMajor() const;
        FString GetMajorString() const;

        TOptional<int32> GetMinor() const;
        FString GetMinorString() const;

        TOptional<int32> GetMicro() const;
        FString GetMicroString() const;

        Gs2::Version::Model::FVersionPtr ToModel() const;
        static TSharedPtr<FEzVersion> FromModel(Gs2::Version::Model::FVersionPtr Model);
    };
    typedef TSharedPtr<FEzVersion> FEzVersionPtr;
}