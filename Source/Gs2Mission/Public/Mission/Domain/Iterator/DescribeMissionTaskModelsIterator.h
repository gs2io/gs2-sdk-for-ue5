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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Mission/Gs2Mission.h"

namespace Gs2::Mission::Domain::Iterator
{

    class FDescribeMissionTaskModelsIteratorLoadTask;

    class GS2MISSION_API FDescribeMissionTaskModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Mission::Model::FMissionTaskModel, FDescribeMissionTaskModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Mission::FGs2MissionRestClientPtr Client;

        friend FDescribeMissionTaskModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeMissionTaskModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> MissionGroupName;
        TOptional<int32> FetchSize;

        FDescribeMissionTaskModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Mission::FGs2MissionRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> MissionGroupName
        );

        class GS2MISSION_API IteratorImpl
        {
            friend FDescribeMissionTaskModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator::FNextTask>> Task;
            Gs2::Mission::Model::FMissionTaskModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Mission::Model::FMissionTaskModelPtr& operator*() const;
            Gs2::Mission::Model::FMissionTaskModelPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeMissionTaskModelsIterator> FDescribeMissionTaskModelsIteratorPtr;

    class FDescribeMissionTaskModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Mission::Model::FMissionTaskModelPtr>>,
        public TSharedFromThis<FDescribeMissionTaskModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeMissionTaskModelsIterator> Self;

    public:
        explicit FDescribeMissionTaskModelsIteratorLoadTask(
            TSharedPtr<FDescribeMissionTaskModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Mission::Model::FMissionTaskModelPtr>>> Result
        ) override;
    };
}
