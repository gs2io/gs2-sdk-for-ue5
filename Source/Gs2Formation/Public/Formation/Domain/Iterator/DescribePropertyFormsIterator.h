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

    class FDescribePropertyFormsIteratorLoadTask;

    class GS2FORMATION_API FDescribePropertyFormsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Formation::Model::FPropertyForm, FDescribePropertyFormsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Formation::FGs2FormationRestClientPtr Client;

        friend FDescribePropertyFormsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribePropertyFormsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        const TOptional<FString> FormModelName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribePropertyFormsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Formation::FGs2FormationRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> FormModelName
        );

        class GS2FORMATION_API IteratorImpl
        {
            friend FDescribePropertyFormsIterator;

            TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator::FNextTask>> Task;
            Gs2::Formation::Model::FPropertyFormPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Formation::Model::FPropertyFormPtr& operator*() const;
            Gs2::Formation::Model::FPropertyFormPtr operator->();
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
    typedef TSharedPtr<FDescribePropertyFormsIterator> FDescribePropertyFormsIteratorPtr;

    class FDescribePropertyFormsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Formation::Model::FPropertyFormPtr>>,
        public TSharedFromThis<FDescribePropertyFormsIteratorLoadTask>
    {
        TSharedPtr<FDescribePropertyFormsIterator> Self;

    public:
        explicit FDescribePropertyFormsIteratorLoadTask(
            TSharedPtr<FDescribePropertyFormsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Formation::Model::FPropertyFormPtr>>> Result
        ) override;
    };
}
