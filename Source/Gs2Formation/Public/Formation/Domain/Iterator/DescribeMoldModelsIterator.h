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
#include "Formation/Gs2Formation.h"

namespace Gs2::Formation::Domain::Iterator
{

    class FDescribeMoldModelsIteratorLoadTask;

    class GS2FORMATION_API FDescribeMoldModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Formation::Model::FMoldModel, FDescribeMoldModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Formation::FGs2FormationRestClientPtr Client;

        friend FDescribeMoldModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeMoldModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeMoldModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Formation::FGs2FormationRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2FORMATION_API IteratorImpl
        {
            friend FDescribeMoldModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIterator::FNextTask>> Task;
            Gs2::Formation::Model::FMoldModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Formation::Model::FMoldModelPtr& operator*() const;
            Gs2::Formation::Model::FMoldModelPtr operator->();
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
    typedef TSharedPtr<FDescribeMoldModelsIterator> FDescribeMoldModelsIteratorPtr;

    class FDescribeMoldModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Formation::Model::FMoldModelPtr>>,
        public TSharedFromThis<FDescribeMoldModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeMoldModelsIterator> Self;

    public:
        explicit FDescribeMoldModelsIteratorLoadTask(
            TSharedPtr<FDescribeMoldModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Formation::Model::FMoldModelPtr>>> Result
        ) override;
    };
}
