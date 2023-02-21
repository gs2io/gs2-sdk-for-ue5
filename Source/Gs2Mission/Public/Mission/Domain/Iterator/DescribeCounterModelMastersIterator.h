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

    class FDescribeCounterModelMastersIteratorLoadTask;

    class GS2MISSION_API FDescribeCounterModelMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Mission::Model::FCounterModelMaster, FDescribeCounterModelMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Mission::FGs2MissionRestClientPtr Client;

        friend FDescribeCounterModelMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeCounterModelMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeCounterModelMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Mission::FGs2MissionRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2MISSION_API IteratorImpl
        {
            friend FDescribeCounterModelMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeCounterModelMastersIterator::FNextTask>> Task;
            Gs2::Mission::Model::FCounterModelMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeCounterModelMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Mission::Model::FCounterModelMasterPtr& operator*() const;
            Gs2::Mission::Model::FCounterModelMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeCounterModelMastersIterator> FDescribeCounterModelMastersIteratorPtr;

    class FDescribeCounterModelMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Mission::Model::FCounterModelMasterPtr>>,
        public TSharedFromThis<FDescribeCounterModelMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeCounterModelMastersIterator> Self;

    public:
        explicit FDescribeCounterModelMastersIteratorLoadTask(
            TSharedPtr<FDescribeCounterModelMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Mission::Model::FCounterModelMasterPtr>>> Result
        ) override;
    };
}
