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
#include "Core/Gs2Object.h"
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FScheduleVersion final : public Gs2Object, public TSharedFromThis<FScheduleVersion>
    {
        TSharedPtr<FVersion> CurrentVersionValue;
        TSharedPtr<FVersion> WarningVersionValue;
        TSharedPtr<FVersion> ErrorVersionValue;
        TOptional<FString> ScheduleEventIdValue;

    public:
        FScheduleVersion();
        FScheduleVersion(
            const FScheduleVersion& From
        );
        virtual ~FScheduleVersion() override = default;

        TSharedPtr<FScheduleVersion> WithCurrentVersion(const TSharedPtr<FVersion> CurrentVersion);
        TSharedPtr<FScheduleVersion> WithWarningVersion(const TSharedPtr<FVersion> WarningVersion);
        TSharedPtr<FScheduleVersion> WithErrorVersion(const TSharedPtr<FVersion> ErrorVersion);
        TSharedPtr<FScheduleVersion> WithScheduleEventId(const TOptional<FString> ScheduleEventId);

        TSharedPtr<FVersion> GetCurrentVersion() const;
        TSharedPtr<FVersion> GetWarningVersion() const;
        TSharedPtr<FVersion> GetErrorVersion() const;
        TOptional<FString> GetScheduleEventId() const;


        static TSharedPtr<FScheduleVersion> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScheduleVersion, ESPMode::ThreadSafe> FScheduleVersionPtr;
}